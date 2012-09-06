--Configuration
local recursive = true
local directory = "."
local outFolder = ""
local chipmunkPath = "../Chipmunk-6.1.1/include/chipmunk"
local namespace = "cp"




local io = require "io"
local lfs = require "lfs"
local table = require "table"
local lpeg = require "lpeg"
lpeg.locale(lpeg)
local space = lpeg.space + lpeg.S"\t\n"

--Table holding all the classes (structs) that are found
local classes = {}
--Table for all typedefs for functions that are found
local functionTypedefs = {}
--Hooks that are called for every function found, if they return nil then the default functions are run
--Otherwise they should return the text for the function and the name of the struct that the method should be added to
local functionHooks = {
	function ( returnType, functionName, argTable )
		if nil and (functionName == "cpArbiterGetShapes" or functionName == "cpArbiterGetBodies") then
			local methodName, struct = getMethod(functionName)
			local argType = toRawStruct(argTable[2].type)
			local paramString = makeRawParameters(argTable)
			paramString = paramString:gsub("&%s*&", "*&")

			for _,v in ipairs(argTable) do
				if _ ~= 1 then
					v.name = "&"..v.name
				end
			end
			local body = argType.." *a_, *b_;\n"
			body = body.."\t\t"..functionName.."("..argTable[1].name..", &a_, &b_);\n"
			body = body.."\t\ta = static_cast<"..toClass(argType).."*>(a_->data);\n"
			body = body.."\t\tb = static_cast<"..toClass(argType).."*>(b_->data);\n"

			local out = "\tinline void "..methodName.."("..paramString..")\n"
			out = out..makeFunctionBody(body)
			return out, struct
		end
	end
	,
	function ( returnType, functionName, argTable )
		if functionName:find("Free") then
			local methodName, struct = getMethod(functionName)
			out = "\t~"..struct:sub(3).."("
			returnIfNotVoid = ""
			local argString = makeRawArguments(argTable, struct, true)
			table.remove(argTable, 1)

			out = out..makeRawParameters(argTable, struct)--Raw
			out = out.. ")\n"

			local body = functionName.."("..argString..");\n"
			if struct:gsub("%s", "") == "cpSpace" then
				body = body.."\t\tbody->"..classes["cpBody"].member.." = 0;\n"
				body = body.."\t\tdelete body;\n"
			end

			out = out..makeFunctionBody(body )
			return out, struct
		end
	end
	,
	function (returnType, functionName, argTable)
		local methodName, struct
		local out =""
		if functionName:find("New") then
			methodName, struct = getMethod(functionName)
			out = "\t"..struct:sub(3).."("
			
			local assignMember = returnType:find(struct) and classes[struct].member or classes[struct].parent.member
			returnIfNotVoid = assignMember.." = "
		elseif functionName:find"Alloc" or functionName:find("Init") or functionName:find"Destroy" then
			return ""--Returning "" to ignore these
		else
			return
		end

		out = out..makeRawParameters(argTable, struct)--Raw

		out = out.. ")\n"
		if classes[struct].parent then
			out = out.."\t : "..classes[struct].parent.name.."(".. functionName.."("..makeRawArguments(argTable, struct).."))\n"
		else
			out= out.."\t : "..classes[struct].member.."("..functionName.."("..makeRawArguments(argTable, struct).."))\n"
		end

		if classes[struct].hasDataPointer then
			local body = classes[struct].member.."->data = this;\n"

			if struct == "cpSpace" then
				out = out.."\t, body(new cp::Body(cpSpaceGetStaticBody("..classes[struct].member..")))\n"
				body = body.."\t\tcpBodySetUserData(cpSpaceGetStaticBody("..classes[struct].member.."), body);\n"
			end
			out = out..makeFunctionBody(body)
		elseif (classes[struct].parent and classes[struct].parent.hasDataPointer) then
			local body = classes[struct].parent.member.."->data = this;\n"
			out = out..makeFunctionBody(body)
		else
			out = out..makeFunctionBody("")
		end

		classes[struct].constructors = classes[struct].constructors..out
		return "", struct
	end
	,
	function (returnType, functionName, argTable )
		for _,v1 in ipairs(argTable) do
			if v1["type"]:find("Func") and functionTypedefs[v1["type"]:gsub("%s*", "")] then
				local originalArgTable = copyTable(argTable)

				local makeFunction = false
				for _,v in ipairs(argTable) do if v.name == "data" then makeFunction = true end end
				if not makeFunction then print("Skipping function: ", functionName) return end
				makeFunction = false
				for _,v in ipairs(argTable) do if v.name == "func" then makeFunction = true end end
				if not makeFunction then print("Skipping function: ", functionName) return end

				local methodName, struct = getMethod(functionName)
				classes[struct].includes["functional"] = "#include <functional>\n"

				local typedef = functionTypedefs[v1["type"]:gsub("%s", "")]
				local functionReturnType = typedef.returnType
				local functionArgs = typedef.args

				local functionParams = makeRawParameters(functionArgs)
				local functionArgs = copyTable(functionArgs)

				for k,v in ipairs(functionArgs) do
					if v.name ~= "data" then 
						local structName = toRawStruct(v.type)
						if v["type"]:find("Arbiter") then 
							v["name"] = "&"..namespace.."::Arbiter("..v.name..")"
						elseif classes[toRawStruct(v.type)] and classes[toRawStruct(v.type)].hasDataPointer then
							v["name"] = "("..namespace.."::"..v["type"]:sub(3)..")"..v.name.."->data"
						end
					else
						table.remove(functionArgs, k)
					end
				end
				local stdFunc = makeStdFunction(functionReturnType, functionArgs)

				local functionTypedef = v1.type:sub(3)
				v1.type = functionTypedef

				classes[struct].additionalText = classes[struct].additionalText.."typedef "..stdFunc..functionTypedef..";\n"

				local returnIfNotVoid = returnType:find("void%s*%**") and "" or "return "
				local stdFuncReturnIfNotVoid = functionReturnType:find("void%s*%**") and "" or "return "
				local anonymousFunctionName = functionName:sub(3)
				local anon = "\t"..functionReturnType..anonymousFunctionName.."("
				anon = anon..functionParams..")"
				
				classes[struct].anonymousDeclarations = classes[struct].anonymousDeclarations..anon..";\n"
				
				anon = anon.."\n"
				anon = anon.."\t{\n"
				anon = anon.."\t\t"..stdFuncReturnIfNotVoid.."(*reinterpret_cast<"..stdFunc.."*>(data))("..makeRawArguments(functionArgs)..");\n"
				anon = anon.."\t}\n\n"
				classes[struct].anonymousDefinitions = classes[struct].anonymousDefinitions..anon

				
				local out = "\tinline "..returnType..methodName.."("

				local funcArgTable = nil
				local dataArgTable = nil
				for _, arg in ipairs(argTable) do
					if arg.name == "data" then
						dataArgTable = arg
					end
					if arg.name == "func" then
						funcArgTable = arg
					end
				end

				local functionReturn = functionReturnType:find("void%s*%**") and "" or "return "
				
				funcArgTable.name = "*"..anonymousFunctionName
				if dataArgTable then  dataArgTable.name = "&func" end

				local argString = makeRawArguments(argTable, struct, true)

				table.remove(argTable, 1)
				table.remove(argTable, #argTable)
				funcArgTable.name ="func"
				
				out = out..makeRawParameters(argTable)
				out = out.. ")\n"
				out = out.."\t{\n"
				out = out.. "\t\t"..returnIfNotVoid..functionName.."("
				out = out..argString
				out = out..");\n"
				out = out.. "\t};\n\n"

				out = out..makeCppMethod(returnType, functionName, originalArgTable)
				return out, struct
			end
		end
	end
	,--cpVect handler since they have different names ie 'cpv...' instead of 'cpVect'
	function (returnType, functionName, argTable )
		if functionName:find("^cpv") then
			if not classes["cpVect"] then

				local includeText = "#pragma once\n\n"
				includeText = includeText.."#include \"chipmunk.h\"\n"
				local classText = ""
				classText = classText.."class Vect : public cpVect{\n"
				classText = classText.."public:\n\n"

				classes["cpVect"] = {name="Vect", text=classText,
									member="", hasMethods=true,
									includeText=includeText, includes={},
									additionalText="", anonymousDefinitions="",
									anonymousDeclarations=""
								}
			end
			local methodName, struct = functionName:gsub("cpv", ""), "cpVect"
			local operatorMap = {
				add={op="+", args="Vect& other"},
				mult={op="*", args="Vect& other"},
				sub={op="-", args="Vect& other"},
				neg={op="-", args="void"},
				eql={op="==", args="Vect& other"}
			}
			local out = ""

			local returnIfNotVoid = returnType:find("void%s*%**") and "" or "return "
			if classes[toRawStruct(returnType)] then
				returnType = toClass(returnType)
			end

			local paramTable = copyTable(argTable)
			if argTable[1].type:find("cpVect") then
				argTable[1].name = "*this"
			end

			if paramTable[1].type:find("cpVect") then
				table.remove(paramTable, 1)
			end
			for _, a in ipairs(paramTable) do 
				if a.type:find("cpVect") then
					a.type = "Vect& "
				end
			end
			local paramString = makeRawParameters(paramTable, struct)

			local argString = makeRawArguments(argTable, struct, true)

			if operatorMap[methodName] then
				local op = operatorMap[methodName].op
				out = "\tinline "..returnType.."operator"..op.."("

				out = out..paramString --Raw
				out = out..")\n"
				out = out..makeFunctionBody(returnIfNotVoid..functionName.."("..argString..");\n")

			elseif methodName ~= "" then
				out = "\tinline "..returnType..methodName.."("
				out = out..paramString
				out = out..")\n"
				out = out..makeFunctionBody(returnIfNotVoid..functionName.."("..argString..");\n")
			else --Methodname is "" meaning it is the constructor 'cpv'
				
				local constructor = "\tVect(cpFloat x=0, cpFloat y=0)\n"
				constructor = constructor.."\t{ this->x = x; this->y = y; }\n\n"

				constructor = constructor.."\tVect(cpVect cv)\n"
				constructor = constructor.."\t{ this->x = cv.x; this->y = cv.y; }\n\n"

				classes[struct].constructors = classes[struct].constructors or ""
				classes[struct].constructors = classes[struct].constructors..constructor
			end
			return out, struct
		end
	end
	,
	function (returnType, functionName, argTable )
		if functionName:find("DataPointer") then
			local memberName = getMethod(functionName)
			return out, struct
		end
	end
}


preWritehooks = {
}

--Fills the table classes with information from all the structs encountered
--This is called before the actual parsing of functions since we need information from
--all of the structs for example if  they have a data pointer
--@dir A string representing the directory to look for files in
--@recursive If the subfolder are to be searched
function buildTypesFromDir( dir, recursive )
	for file in lfs.dir(dir) do
		local fullName = dir.."/"..file
		if file:find("%.h") and file:sub(1,2) == "cp" then
			local f = assert(io.open(dir.."/"..file))
			local text = f:read("*all")
			f:close()
			buildTypes(text)
		elseif recursive and file ~= "." and file ~= ".." and lfs.attributes(fullName, "mode") =="directory" then
			buildTypesFromDir(fullName, recursive)
		end
	end
end

--Parses the files in dir for functions
--@dir A string representing the directory to look for files in
--@recursive If the subfolder are to be searched
function parseTextFromDir( dir, recursive )
	for file in lfs.dir(dir) do
		local fullName = dir.."/"..file
		if file:find("%.h") and file:sub(1,2) == "cp" then
			local f = assert(io.open(dir.."/"..file))
			local text = f:read("*all")
			f:close()
			parseText(text)
		elseif recursive and file ~= "." and file ~= ".." and lfs.attributes(fullName, "mode") =="directory" then
			parseTextFromDir(fullName, recursive)
		end
	end
end

--Main function which calls the build and parse functions as well as outputting the text
function parseDir(dir, recursive)
	buildTypesFromDir(dir, recursive)
	parseTextFromDir(dir, recursive)

	for _,hook in ipairs(preWritehooks) do
		hook()
	end
	writeClasses()

	writeDeclarations()

	writeIncludeAll()
end

function writeDeclarations()
	local declarationText = "#pragma once\n"
	declarationText = declarationText.."//Forward declarations\n"
	declarationText= declarationText.."namespace "..namespace.."{\n"
	for _, v in pairs(classes) do 
		if v.hasMethods then
			declarationText = declarationText.."\tclass "..v.name..";\n"
		end
	end
	declarationText = declarationText.."}\n\n"

	writeFile(outFolder.."chipmunk_declarations.hpp", declarationText)
end

function writeIncludeAll()
	local includeAllText = "#pragma once\n"
	includeAllText = includeAllText.."#include \"chipmunk_declarations.hpp\"\n"
	--Need to include Vect and BB first since they are used by value and not only by pointer
	includeAllText = includeAllText..'#include "Vect.hpp"\n#include "BB.hpp"\n'
	for k,v in pairs(classes) do
		if v.hasMethods then
			includeAllText = includeAllText..'#include "'..v.name..'.hpp"\n'
		end
	end

	writeFile(outFolder.."chipmunk.hpp", includeAllText)
end

--Writes all the class files using the global table 'classes'
function writeClasses( )
	for k,v in pairs(classes) do
		for structName,_ in pairs(classes) do
			local class = toClass(structName)
			if k ~= structName and classes[structName] and classes[structName].hasMethods 
				and (v.text:find(class) or v.constructors:find(class) or v.anonymousDefinitions:find(class)) then

				v.includes[class:gsub("^.*::", "")] = true
			end
		end


		for includeClass, includeText in pairs(v.includes) do
			if type(includeText) == "string" then 
				v.includeText = v.includeText..includeText
			else
				v.includeText = v.includeText.."#include \""..includeClass..".hpp\"\n"
			end
		end

		if v.hasMethods then
			if k == "cpSpatialIndex" then
				v.text = v.text:gsub("dynamicIndex", "index->dynamicIndex")--TODO
			end
			local className = k:sub(3)
			local outName = className..".hpp"
			if v.parent then
				v.includeText = v.includeText..'#include "'..v.parent.name..'.hpp"\n'
				v.text = v.text:gsub("class "..className, "class "..className.." : public "..v.parent.name)
			end

			local out = v.includeText.."\n"

			if v.anonymousDeclarations and v.anonymousDeclarations ~= "" then 
				out = out.."class "..v.name..";\n".."namespace {\n"..v.anonymousDeclarations.."}\n\n"
			end

			out = out.. "namespace "..namespace.." {\n\n"
			if v.additionalText then
				out = out..v.additionalText.."\n"
			end
			out = out.. v.text..v.constructors
			out = out.. "};\n"
			out = out.. "}//namespace "..namespace.."\n"

			if v.anonymousDefinitions and v.anonymousDefinitions  ~= "" then 
				out = out.."\nnamespace {\n"..v.anonymousDefinitions.."}"
			end
			writeFile(outFolder..outName, out)
		end
	end
end

--Compares the text with what is already there to determine if we need to update it
--TODO : Should maybe compare timestamps instead
function writeFile( filename, text )
	local f = assert(io.open(filename))
	local previousText = f:read("*all")
	f:close()
	if previousText ~= text then
		local f = assert(io.open(filename, "w"))
		f:write(text)
		f:close()
	end
end

local I = lpeg.Cp()
--Call with a lpeg pattern to search the whole file for the pattern
function anywhere (p)
  return lpeg.P{ I * p * I + 1 * lpeg.V(1) }--Capture the positions before and after the pattern
end
local allowed = lpeg.alpha + lpeg.P("_") + lpeg.R("09")--Alowed characters in a variable name


--Returns a pattern that matches a argument list in a C function
function makeArgumentPattern( )
	local argType = (("const" * lpeg.space^1 * allowed^1) + allowed^1) * (lpeg.space + lpeg.S"*")^1
	local argument = lpeg.Cg((lpeg.C(argType) * lpeg.C(allowed^1)) + lpeg.C"void")


	local arguments = lpeg.Cf(lpeg.Ct("") * argument * (space^0 * "," * space^0 * argument * space^0)^0
			* space^0,
	function (tab, argumentType , argumentName)
		table.insert(tab, {["type"]=argumentType, ["name"]=argumentName})
		return tab
	end)
	return arguments
end

--Returns a pattern that matches a C function
function makeFunctionPattern( )
	local func = lpeg.C(("const " + lpeg.P"") * allowed^1 * lpeg.S" *"^0) *
			lpeg.C(allowed^1) * space^0 * lpeg.S"(" * space^0 * makeArgumentPattern() * space^0 * lpeg.S")"
	return func
end


---------------------------------------
--Patterns
local functionPattern = makeFunctionPattern()
local structPattern = "struct" * space^1 * lpeg.C(allowed^1) *((space^1 * allowed^1 * ";") + (space^0 * "{"))
local propertyPattern = "\n" * space^0 * lpeg.P"CP_" * lpeg.C(lpeg.P"Define" + lpeg.P"Declare") * lpeg.C(allowed^1) 
	* space^0 * "(" 
	* space^0 * lpeg.C((allowed + "*")^1) * space^0 * ","
	* space^0 * lpeg.C((allowed + lpeg.S"())")^1) * space^0 * ","
	* space^0 * lpeg.C(allowed^1)
	* ((space^0 * "," * space^0 * lpeg.C(allowed^1)) + "")

local typedefPattern = "typedef" * space^1 * lpeg.C(allowed^1 * space^0 * lpeg.P"*"^0) * space^0 * "("
	* space^0 * "*" * space^0 * lpeg.C(allowed^1) * space^0 * ")" * space^0 * "("
	* makeArgumentPattern() * ")" * space^0 * ";"


--Calls the callback with all the values that are returned from the pattern matching
function matchAll( pattern, text, callback )
	local i = 1
	local length = #text
	while i < length do
		local a = {anywhere(pattern):match(text, i)}
		if a[1] then
			i = callback(unpack(a))
		end
		i = i+1
	end
end

--Copy the table
--WARNING: Does not work for tables that are cyclic
function copyTable( tab )
	local c = {}
	for k,v in pairs(tab) do
		if type(v) == "table" then
			c[k] = copyTable(v)
		else
			c[k] = v
		end
	end
	for k,v in ipairs(tab) do
		if type(v) == "table" then
			c[k] = copyTable(v)
		else
			c[k] = v
		end
	end
	return c
end

--Returns the method and struct if they could be deduced from the functions name
function getMethod(func )
	local bestMatch, key = func, ""
	for k,v in pairs(classes) do
		if func:find("^"..k) and #k > #key then
			bestMatch, key = func:gsub(k, ""), k
		end
	end
	if key ~= "" then 
		if bestMatch:sub(1,2) == "BB" then return bestMatch, key end
		return bestMatch:sub(1,1):lower()..bestMatch:sub(2), key 
	end
	if func:find("cpBoxShape") then
		local methodName = func:gsub("cpBoxShape", "")
		return methodName:sub(1,1):lower()..methodName:sub(2), "cpPolyShape"
	elseif func:find("^cpv") then
		local methodName = func:gsub("^cpv", "cpVect")
		return methodName:sub(1,1):lower()..methodName:sub(2), "cpVect"
	end
	print("Could not find class for function:", func)
	return func
end

--Returns a string for a std::function<> that returns 'functionReturnType' and takes the 
--arguments 'functionArgs'
function makeStdFunction(functionReturnType, functionArgs)
	local stdFunc = "std::function<"..functionReturnType.."("
	for _,a in ipairs(functionArgs) do 
		if a.type:sub(1,2) == "cp" and classes[toRawStruct(a.type)] and classes[toRawStruct(a.type)].hasMethods then
			stdFunc = stdFunc..namespace.."::"..a["type"]:sub(3)..","
		else
			stdFunc = stdFunc..a["type"]..","
		end
	end
	if stdFunc:sub(#stdFunc) == "," then stdFunc = stdFunc:sub(1, #stdFunc-1) end
	stdFunc = stdFunc..")> "
	return stdFunc
end

function makeReturn(returnType )
	if returnType == "void" then return "" end
end

--Removes any spaces and pointers to a struct
function toRawStruct( struct )
	local out = struct:gsub("%s*", ""):gsub("%*", ""):gsub("::", "")
	return out
end

function toClass( struct )
	if namespace == "" then return struct:sub(3) end
	return namespace.."::"..struct:sub(3)
end

--Makes a parameter list from a table without any modifcations
--tab[i] = {name="body", type="cpBody *"}
function makeRawParameters(tab )
	local out = ""
	for k,v in ipairs(tab) do
		if not v.name then v.name = "" end
		--if v.type == "cpVect " then v.type = "cpVect& " end
		out = out..v["type"]..v["name"]..","
	end
	if out:sub(#out) == "," then
		out = out:sub(1, #out-1)
	end
	return out
end

--tab[i] = {name="body", type="cpBody *"}
function makeParameters(tab, struct )
	local out = ""
	for k,v in ipairs(tab) do
		if not v.name then v.name = "" end
		v.type = v.type:gsub("cpVect ", namespace.."::Vect& ")
		v.type = v.type:gsub("cpBB ", namespace.."::BB& ")
		if classes[toRawStruct(v.type)] and classes[toRawStruct(v.type)].hasMethods then
			v.type = "const "..toClass(v.type):gsub("%s*%*%s*", "& ")
		end
		out = out..v["type"]..v["name"]..","
	end
	if out:sub(#out) == "," then
		out = out:sub(1, #out-1)
	end
	return out
end

--Makes a argument list from a table without any modifcations
--that are to be used in a function call
--tab[i] = {name="body", type="cpBody *"}
function makeRawArguments( tab )
	local out = ""
	for k,v in ipairs(tab) do
		if v.name then
			out = out..v.name..","
		end
	end
	if out:sub(#out) == "," then
		out = out:sub(1, #out-1)
	end
	return out
end

function makeArguments(tab, struct, firstArgIsThis)
	local out = ""
	for k,v in ipairs(tab) do
		if classes[toRawStruct(v.type)] and classes[toRawStruct(v.type)].hasMethods then 
			if v.name == "" then
				out = out.."get(),"
			else
				out = out..v.name..".get(),"
			end
		elseif v.name then
			if v.name == "" then
				out = out.."get(),"
			else
				out = out..v.name..","
			end
		end
	end
	if out:sub(#out) == "," then
		out = out:sub(1, #out-1)
	end
	return out
end

function makeDeclaration(returnType, methodName, argTable )
	local out = "\t"..returnType..methodName.."(".. makeRawParameters(argTable)..")"
	return out
end

function makeFunctionBody( body)
	local out = "\t{\n\t\t"..body.."\t}\n\n"
	return out
end

function makeMethod(returnType, methodName, argTable , body)
	return makeDeclaration(returnType, methodName, argTable )..makeFunctionBody( body)
end


--The standard function that creates a method for c++
--This should be able to handle 90% of all chipmunk methods
function makeCppMethod(returnType, functionName, tab )

	local returnIfNotVoid = returnType:find("void%s*%**") and "" or "return "
	local methodName, struct = getMethod(functionName)
	local returnStruct = toRawStruct(returnType) --We need the struct without it being a pointer to check if it is a type we have a class for
	
	if returnIfNotVoid ~= "" and classes[returnStruct] and classes[returnStruct].hasMethods and struct then 
		returnType = toClass(returnType)
	end
	local out = "\tinline "..returnType..methodName.."("


	if tab[1] and classes[struct] then
		if tab[1].type:find( struct) then
			tab[1].name = classes[struct].member
		end
	end
	local argString = makeRawArguments(tab, struct, true)
	table.remove(tab, 1)
	out = out..makeRawParameters(tab, struct)--Raw

	out = out.. ")\n"
	local body = functionName.."("..argString..")"

	if returnIfNotVoid ~= "" and classes[returnStruct] and struct 
		and classes[struct].hasDataPointer and returnType:find("%*") then
		body = returnType:gsub("^.*::", "cp").." temp = "..body..";\n"
		body = body.."\t\treturn static_cast<"..returnType..">(temp ? temp->data : 0)"
	else
		body = returnIfNotVoid..body
	end
	out = out..makeFunctionBody(body..";\n")

	return out, struct
end


--Takes some text and fills the table 'classes' with all the structs it finds
--and fills the table 'functionTypedefs' with all the typedefd functions it finds
function buildTypes( text )
	matchAll(structPattern, text, 
	function (b, structName, e)
		local chipmunkMember = structName:lower():sub(3)
		if chipmunkMember == "arbiter" then chipmunkMember = "arb"
		elseif chipmunkMember == "spatialindex" then chipmunkMember = "index"
		elseif chipmunkMember == "spacehash" then chipmunkMember = "hash"
		end

		local includeText = "#pragma once\n\n"
		includeText = includeText.."#include \"chipmunk.h\"\n"

		--Hacked in to let Vect and BB not be pointers
		local pointer = (structName=="cpVect" or structName == "cpBB") and " " or "*"
		--Check to see if the struct has a datapointer, if that is the case we will use that to store the pointer
		--back to the class in c++ that is conataining thepointer to the struct in c
		local hasDataPointer = false
		local data_b, data_e = text:find("cpDataPointer%s+data;", e)
		local nextBrace = text:find("}", b)
		if data_b and data_b < nextBrace then --There should be a data pointer in this class
			hasDataPointer = true
		end
		local className = structName:sub(3)
		local classText = ""
		classText = classText.."class "..className.."{\n"

		classText = classText.."protected:\n"
		classText = classText.."\t"..structName..pointer..chipmunkMember..";\n"

	
		if hasDataPointer then
			classText = classText.."private:\n"
			classText = classText.."\tcpDataPointer data;\n"
		end
		if structName == "cpSpace" then --We add a cp::Body* as well for the static body
			classText = classText.."\t"..namespace.."::Body* body;\n"
		end
		if structName == "cpBody" then
			classText = classText.."\tfriend class "..namespace.."::Space;\n"
		end

		classText = classText.."public:\n\n"

		local hasMethods = text:find("%w+%s*"..structName.."[_%w]+%s*%(")
		--Construct from a pointer to a cpStruct
		
		local body = chipmunkMember.." = v;\n"
		if hasDataPointer then
			body = body.."\t\tdata = v->data;\n"
			body = body.."\t\tv->data = this;\n"
		end

		local constructors = "\t"..className.."("..structName..pointer.." v)\n"
		constructors = constructors..makeFunctionBody(body)

		classText = classText.."\t"..structName..pointer.." get() const\n"
		classText = classText..makeFunctionBody("return "..chipmunkMember..";\n")

		classText = classText.."\toperator "..structName..pointer.."() const\n"
		classText = classText.."\t{\n"
		classText = classText.."\t\treturn "..chipmunkMember..";\n"
		classText = classText.."\t}\n\n"

		function setIfNotNil( structName, field, val)
			classes[structName][field] = classes[structName][field] or val
		end
		classes[structName] = classes[structName] or {}
		setIfNotNil(structName, "name", className)
		setIfNotNil(structName, "text", classText)
		setIfNotNil(structName, "member", chipmunkMember)
		setIfNotNil(structName, "hasMethods", hasMethods)
		setIfNotNil(structName, "includeText", includeText)
		setIfNotNil(structName, "includes", {})
		setIfNotNil(structName, "additionalText", "")
		setIfNotNil(structName, "anonymousDeclarations", "")
		setIfNotNil(structName, "anonymousDefinitions", "")
		setIfNotNil(structName, "hasDataPointer", hasDataPointer)
		setIfNotNil(structName, "constructors", constructors)
		return e
	end)

	matchAll(typedefPattern, text,
		function ( b,returnType, name, argTable,e)
			functionTypedefs[name] = {
				returnType= returnType,
				args=argTable
			}
			return e
		end)

	if classes["cpPolyShape"] then
		classes["cpShape"] = classes["cpShape"] or {}
		classes["cpPolyShape"].parent = classes["cpShape"]
		classes["cpPolyShape"].constructors = ""
	end
	if classes["cpCircleShape"] then
		classes["cpShape"] = classes["cpShape"] or {}
		classes["cpCircleShape"].parent = classes["cpShape"]
		classes["cpCircleShape"].constructors = ""
	end
	if classes["cpSegmentShape"] then
		classes["cpShape"] = classes["cpShape"] or {}
		classes["cpSegmentShape"].parent = classes["cpShape"]
		classes["cpSegmentShape"].constructors = ""
	end
	if classes["cpBBTree"] then
		classes["cpBBTree"] = classes["cpBBTree"] or {}
		classes["cpBBTree"].parent = classes["cpSpatialIndex"]
		classes["cpBBTree"].constructors = ""
	end
	if classes["cpSpaceHash"] then
		classes["cpSpaceHash"] = classes["cpSpaceHash"] or {}
		classes["cpSpaceHash"].parent = classes["cpSpatialIndex"]
		classes["cpSpaceHash"].constructors = ""
	end
	if classes["cpSweep1D"] then
		classes["cpSweep1D"] = classes["cpSweep1D"] or {}
		classes["cpSweep1D"].parent = classes["cpSpatialIndex"]
		classes["cpSweep1D"].constructors = ""
	end

	for k,v in pairs(classes) do 
		if k:find("Joint") or k:find("Spring") or k:find("Motor") then
			v.parent = classes["cpConstraint"]
			v.constructors = ""
		end
	end
end



--Parses the text for any functions that it finds as well as any property macros
function parseText(text )
	matchAll(functionPattern, text,
		function (b, returnType, functionName, tab, e)
		if b then
			if functionName:find("AddCollisionHandler") then
				print(functionName)
			end
			local _, struct = getMethod(functionName)
			if struct and classes[struct] then
				classes[struct].hasMethods = true
			end
			--local out, struct = makeMethod(returnType, functionName, tab)
			local out, struct = nil, nil
			for _,hook in ipairs(functionHooks) do
				out, struct = hook(returnType, functionName, tab)
				if out then break end
			end

			if not out then
				out, struct = makeCppMethod(returnType, functionName, tab)
			end

			--assert(struct == cppStruct)
			if struct then
				classes[struct].text = classes[struct].text..out
				classes[struct].hasMethods = true
			end
		end
		return e--return the new position
	end)

	matchAll(propertyPattern, text,
		function (...)
			local b = arg[1]
			local defineOrDeclare = arg[2]
			local defineText = arg[3]
			local structType = arg[4]
			local member = arg[5]
			local name = arg[6]
			local e = arg[#arg]
			local extra = (arg[#arg - 1] == arg[6]) and nil or arg[#arg -1]

			if name == "name" or extra == "name" then --The #define of the macro which we must ignore
				return e
			end 
			local type = structType

			local class = defineText:gsub("Struct",""):gsub("Property",""):gsub("Getter",""):gsub("Setter", "")
			local structMember = classes["cp"..class].member
			
			if defineText:find("Constraint[^S][^t][^r][^u][^c][^t]") then --The properties of a constraint has four argument where the first is the "sublclass"
				class = type:sub(3)
				type = member
				name = extra
				structMember = "constraint"
			end

			if defineOrDeclare == "Declare" then 
				class = type:sub(3)
				structMember = classes["cp"..class].parent and classes["cp"..class].parent.member or structMember
				type = member
			end

			local getter = true
			local setter = true
			if defineText:find("Setter") then getter = false
			elseif defineText:find("Getter") then setter = false end
			local out = ""
			if getter then
				local body = "return cp"..class.."Get"..name.."("..structMember..");\n"
				local rawStruct = toRawStruct(structType)
				local returnType = type
				if classes[rawStruct] and classes[rawStruct].hasDataPointer then
					returnType = toClass(rawStruct).."*"
					local f = "cp"..class.."Get"..name.."("..structMember..")"
					body = "return static_cast<"..returnType..">("..f.." ? "..f.."->data : 0);\n"
				elseif rawStruct == "cpDataPointer" then
					body = "return data;\n"
				elseif returnType == "cpVect" or returnType == "cpBB" then
					returnType = toClass(returnType)
				end

				out = out.."\tinline "..returnType.." get"..name.."(void)\n"
				out = out..makeFunctionBody(body)
			end
			if setter then
				local body = "cp"..class.."Set"..name.."("..structMember..",value);\n"
				if toRawStruct(structType) == "cpDataPointer" then
					body = "data = value;\n"
				elseif type == "cpVect" or type =="cpBB" then
					type = toClass(type).."&"
				end
				out = out.."\tinline void".." set"..name.."("..type.." value)\n"
				out = out..makeFunctionBody(body)
			end

			classes["cp"..class].text = classes["cp"..class].text..out
			classes["cp"..class].hasMethods = true
			return e
		end)

end


parseDir(chipmunkPath, recursive)
