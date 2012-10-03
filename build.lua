--Configuration
local recursive = true
local directory = "."
local outFolder = ""
local chipmunkPath = "../Chipmunk-6.1.1/include/chipmunk"
local namespace = "cp"


local io = require "io"
local table = require "table"


local lfs = require "lfs"
local lpeg = require "lpeg"
lpeg.locale(lpeg)
local space = lpeg.space + lpeg.S"\t\n"

if not lfs.attributes(outFolder) then
	lfs.mkdir(outFolder)
	lfs.mkdir(outFolder.."src")
	lfs.mkdir(outFolder.."include")
end

local timestamp = 
[[
/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on ]]..os.date()..[[.
 */
]]


--Table holding all the classes (structs) that are found
local classes = {}
--Table for all typedefs for functions that are found
local functionTypedefs = {}
--Hooks that are called for every function found, if they return nil then the default functions are run
--Otherwise they should return the text for the function and the name of the struct that the method should be added to
local functionHooks = {
	function ( returnType, functionName, argTable  )
		if functionName == "cpBodySanityCheck" then
			return ""
		end
	end
	,
	function ( returnType, functionName, argTable  )
		if functionName == "cpSpaceRemoveCollisionHandler" then
			local methodName, struct = getMethod(functionName)
			local class = classes[struct]
			table.insert(class.members, {
				type="std::unordered_map<std::pair<cpCollisionType, cpCollisionType>,CollisionHandler, HashFunctor> ",
				name="collisionHandlers;"
			})
			table.insert(class.includes, "#include <unordered_map>\n")

			local body = "collisionHandlers.erase(std::make_pair(a, b));\n"
			body = body..functionName.."("..makeArguments(argTable)..");\n"
			table.remove(argTable, 1)
			return 	Method:new({
				returnType="void ",
				name="removeCollisionHandler",
				body=body,
				parameters=argTable
				}
				),
				struct
		end
	end
	,
	function ( returnType, functionName, argTable )
		if functionName == "cpSpaceAddCollisionHandler" then

			local methodName, struct = getMethod(functionName)
			local class = classes[struct]
			classes.cpSpace.additionalText =classes.cpSpace.additionalText..
[[	struct CollisionHandler {
		std::function<cpBool (cp::Arbiter *arb, cp::Space *space, void *data)> begin;
		std::function<cpBool (cp::Arbiter *arb, cp::Space *space, void *data)> preSolve;
		std::function<void (cp::Arbiter *arb, cp::Space *space, void *data)> postSolve;
		std::function<void (cp::Arbiter *arb, cp::Space *space, void *data)> separate;
		cpDataPointer data;
	};

	struct HashFunctor {
		size_t operator()(const std::pair<cpCollisionType, cpCollisionType> p) const
		{
			return (size_t)(p.first)*3344921057ul ^ (size_t)(p.second)*3344921057ul;
		}
	};
]]
			local functionArgs = copyTable(argTable)
			local body = 
			[[CollisionHandler& handler = collisionHandlers[std::make_pair(a,b)];
			handler.begin = begin;
			handler.preSolve = preSolve;
			handler.postSolve = postSolve;
			handler.separate = separate;
			handler.data = data;
			cpSpaceAddCollisionHandler(]]

			for k,v in ipairs(functionArgs) do 
				local cpTypedef = functionTypedefs[v.type:gsub("%s*", "")]
				if cpTypedef then
					local stdFunc = makeStdFunction(cpTypedef.returnType, cpTypedef.args)
					local typedefName = toClass(v.type):gsub(getNamespace(), "")
					class.additionalText = class.additionalText.."\ttypedef "..stdFunc..typedefName..";\n"

					v.type = typedefName
					local returnIfNotVoid = cpTypedef.returnType:gsub("%s+", "") == "void" and "" or "return"
					body = body.."!"..v.name.." ?  0 : internal_"..typedefName..", "
					local fun = "\t"..cpTypedef.returnType.."internal_"..typedefName.."("..makeRawParameters(cpTypedef.args)..")"
					class.anonymousDeclarations = class.anonymousDeclarations..fun..";\n"
					fun = fun.."\n\t{\n"
					fun = fun.."\t\t"..getNamespace().."CollisionHandler* handler = static_cast<"..getNamespace().."CollisionHandler*>(data);\n"
					local anonArgs = copyTable(cpTypedef.args)
					for _, arg in ipairs(anonArgs) do
						if arg.type:find("cpArbiter") then
							fun = fun.."\t\t"..getNamespace().."Arbiter tempArbiter("..arg.name..");\n"
							arg.name = "&tempArbiter"
						elseif arg.name ~= "data" then
							arg.name = "static_cast<"..toClass(arg.type)..">("..arg.name.."->data)"
						end
					end
					local returnTrueOrVoid = cpTypedef.returnType == "void " and "" or " true"
					fun = fun.."\t\tdata = handler->data;\n"
					fun = fun.."\t\treturn (handler->"..v.name..")("..makeRawArguments(anonArgs)..");\n"
					fun = fun.."\t}\n"
					class.anonymousDefinitions = 
					class.anonymousDefinitions..fun

					v.default = typedefName.."()"
					v.type = "const "..v.type.."& "
				else
					body = body..v.name..", "
					if v.name == "data" then v.default = 0 end
				end
			end
			body = body:sub(1, #body - #" data,").." &handler);\n"

			--remove the first paramter
			table.remove(functionArgs, 1)
			toCppTypes(functionArgs)
			class:addMethod(Method:new({
				returnType="void ",
				name="addCollisionHandler",
				body=body,
				parameters=functionArgs
				}
				))
			--Fall through to declare the normal method as well
			return
		end
	end
	,
	function ( returnType, functionName, argTable  ) --Hacked in until I know how to deal with this constructor
		if functionName == "cpPolyShapeNew" then
			local _, struct = getMethod(functionName)
			local initializerList = {{
				lvalue="Shape",
				rvalue=functionName.."("..makeRawArguments(argTable):gsub("body", "body ? body->get() : 0")..")"
			}}
			argTable[1].type = getNamespace().."Body *"
			return Method:new(
				{ returnType="",
				  name="PolyShape", 
				  body="",
				  parameters=argTable,
				  initializerList=initializerList
				  }),
				  struct
		end
	end
	,
	function ( returnType, functionName, argTable )
		if (functionName == "cpArbiterGetShapes" or functionName == "cpArbiterGetBodies") then
			local methodName, struct = getMethod(functionName)
			local argType = toRawStruct(argTable[2].type)

			for _,v in ipairs(argTable) do
				if _ ~= 1 then
					v.type = toClass(v.type):gsub("%*%*", "*")
					v.name = "&"..v.name
				end
			end
			local body = argType.." *a_, *b_;\n"
			body = body.."\t\t"..functionName.."("..argTable[1].name..", &a_, &b_);\n"
			body = body.."\t\ta = static_cast<"..toClass(argType).."*>(a_->data);\n"
			body = body.."\t\tb = static_cast<"..toClass(argType).."*>(b_->data);\n"

			table.remove(argTable, 1)
			return Method:new({ returnType=returnType, name=methodName, body=body, parameters=argTable}), struct
		end
	end
	,
	function ( returnType, functionName, argTable )
		if functionName:find("Free") then
			local methodName, struct = getMethod(functionName)
			methodName = "~"..struct:sub(3)
			returnType = ""
			local argString = makeRawArguments(argTable, struct, true)
			table.remove(argTable, 1)

			local body = functionName.."("..argString..");\n"
			if struct:gsub("%s", "") == "cpSpace" then
				body = body.."\t\tbody->"..classes["cpBody"].member.." = 0;\n"
				body = body.."\t\tdelete body;\n"
			end

			return Method:new({ returnType=returnType, name=methodName, body=body, parameters=argTable}), struct
		end
	end
	,
	function (returnType, functionName, argTable)
		local methodName, struct
		
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
		methodName=classes[struct].name

		toCppTypes(argTable)
		local args = copyTable(argTable)
		addGetCall(args, struct)
		firstArg(args, struct)

		local initializerList = { }
		if type(classes[struct].parent) == "table" then
			table.insert(initializerList, {
				lvalue=classes[struct].parent.name,
				rvalue=functionName.."("..makeRawArguments(args, struct)..")"
			})
		elseif type(classes[struct].parent) == "string" then
			table.insert(initializerList, {
				lvalue=classes[struct].parent,
				rvalue=functionName.."("..makeRawArguments(args, struct)..")"
			})
		else
			table.insert(initializerList, {
				lvalue=classes[struct].member,
				rvalue=functionName.."("..makeRawArguments(args, struct)..")"
			})
		end
		local body = ""
		if classes[struct].hasDataPointer then
			table.insert(initializerList,{
				lvalue="data",
				rvalue="0"
			})

			body = classes[struct].member.."->data = this;\n"

			if struct == "cpSpace" then
				table.insert(initializerList,{
					lvalue="body",
					rvalue="new cp::Body(cpSpaceGetStaticBody("..classes[struct].member.."))"
				})
				body = body.."\t\tcpBodySetUserData(cpSpaceGetStaticBody("..classes[struct].member.."), body);\n"
			end
		elseif (classes[struct].parent and classes[struct].parent.hasDataPointer) then
			body = classes[struct].parent.member.."->data = this;\n"
		end

		classes[struct].constructors = classes[struct].constructors..out
		return Method:new({ 
			returnType="", name=methodName, 
			body=body, parameters=argTable,
			initializerList=initializerList
			}), 
		struct
	end
	,
	function (returnType, functionName, argTable )
		for _,v1 in ipairs(argTable) do
			if v1["type"]:find("Func") and functionTypedefs[v1["type"]:gsub("%s*", "")] then
				if argTable[1].name == "dynamicIndex" then argTable[1].name = "index" end
				local originalArgTable = copyTable(argTable)

				local makeFunction = false
				for _,v in ipairs(argTable) do if v.name == "data" then makeFunction = true end end
				if not makeFunction then print("Skipping std::function for : ", functionName) return end
				makeFunction = false
				for _,v in ipairs(argTable) do if v.name == "func" then makeFunction = true end end
				if not makeFunction then print("Skipping std::function for : ", functionName) return end

				local methodName, struct = getMethod(functionName)
				classes[struct].includes["functional"] = "#include <functional>\n"

				local typedef = functionTypedefs[v1["type"]:gsub("%s", "")]
				local functionReturnType = typedef.returnType
				local functionArgs = typedef.args

				local functionParams = makeRawParameters(functionArgs)
				local functionArgs = copyTable(functionArgs)
				local anonymousBody = ""

				for k,v in ipairs(functionArgs) do
					if v.name ~= "data" then 
						local structName = toRawStruct(v.type)
						if v["type"]:find("Arbiter") then 
							anonymousBody = anonymousBody..namespace.."::Arbiter tempArbiter("..v.name..");\n"
							v["name"] = "&tempArbiter"
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
				classes[struct].additionalText = classes[struct].additionalText..typedef.comment.."\ttypedef "..stdFunc..functionTypedef..";\n"

				local returnIfNotVoid = returnType:find("void%s*%**") and "" or "return "
				local stdFuncReturnIfNotVoid = functionReturnType:find("void%s*%**") and "" or "return "
				local anonymousFunctionName = functionName:sub(3)
				local anon = "\t"..functionReturnType..anonymousFunctionName.."("
				anon = anon..functionParams..")"
				
				classes[struct].anonymousDeclarations = classes[struct].anonymousDeclarations..anon..";\n"
				
				anonymousBody = anonymousBody.."\t\t"..stdFuncReturnIfNotVoid.."(*reinterpret_cast<"..stdFunc.."*>(data))("..makeRawArguments(functionArgs)..");\n"

				classes[struct].anonymousDefinitions = classes[struct].anonymousDefinitions..anon.."\n"..makeFunctionBody(anonymousBody)

				

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

				local body = returnIfNotVoid..functionName.."("..argString..");\n"
				
				--Add a method that does not use std::function as well
				local t = makeCppMethod(returnType, functionName, originalArgTable)
				classes[struct]:addMethod( t)

				return Method:new({ returnType=returnType, name=methodName, body=body, parameters=argTable}), struct
			end
		end
	end
	,--cpVect handler since they have different names ie 'cpv...' instead of 'cpVect'
	function (returnType, functionName, argTable )
		if functionName:find("^cpv") then
			local methodName, struct = functionName:gsub("cpv", ""), "cpVect"
			local operatorMap = {
				add={op="+", args="Vect& other"},
				mult={op="*", args="Vect& other"},
				sub={op="-", args="Vect& other"},
				neg={op="-", args="void"},
				eql={op="==", args="Vect& other"}
			}


			local returnIfNotVoid = returnType:find("void%s*%**") and "" or "return "
			if classes[toRawStruct(returnType)] then
				returnType = toClass(returnType)
			end

			local args = copyTable(argTable)
			if args[1].type:find("cpVect") then
				args[1].name = "*this"
			end

			if argTable[1].type:find("cpVect") then
				table.remove(argTable, 1)
			end
			for _, a in ipairs(argTable) do 
				if a.type:find("cpVect") then
					a.type = "Vect& "
				end
			end

			local argString = makeRawArguments(args, struct, true)
			local body = ""

			if operatorMap[methodName] then
				local op = operatorMap[methodName].op
				body = returnIfNotVoid..functionName.."("..argString..");\n"
			elseif methodName ~= "" then
				body = returnIfNotVoid..functionName.."("..argString..");\n"
			else --Methodname is "" meaning it is the constructor 'cpv'
				
				methodName = "Vect"
				returnType = ""
				argTable[1].default = 0
				argTable[2].default = 0
				body = "this->x = x; this->y = y;\n"


				classes[struct]:addMethod(Method:new({ 
					returnType="", 
					name="Vect", 
					body="this->x = cv.x; this->y = cv.y;\n", 
					parameters={{type="cpVect ", name="cv"}}
					}))
			end

			return Method:new({ returnType=returnType, name=methodName, body=body, parameters=argTable}), struct
		end
	end
	,
	function (returnType, functionName, argTable )
		if functionName:find("DataPointer") then
			local methodName, struct = getMethod(functionName)
			local body = "return data;\n"
			return Method:new({ returnType=returnType, name=methodName, body=body, parameters=argTable}), struct
		end
	end
}


preWritehooks = {
	function ( ... )

		for structName,class in pairs(classes) do
			if not class.parent then
				local pointer = (structName=="cpVect" or structName == "cpBB") and " " or "*"
				local body = class.members[1].name.." = v;\n"
				local initializerList = nil

				if class.hasDataPointer then
					body = body.."\t\tdata = v->data;\n"
					body = body.."\t\tv->data = this;\n"
					initializerList = {{
						lvalue="data",
						rvalue="0"
					}}
				end


				class:addMethod(Method:new({
				name=class.name,
				body=body,
				returnType="",
				parameters= {{type=structName..pointer.." ", name="v"}},
				initializerList=initializerList
				})
				)	
			end
		end
	end
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

	writeFile(outFolder.."include/".."chipmunk_declarations.hpp", declarationText)
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

	writeFile(outFolder.."include/".."chipmunk.hpp", includeAllText)
end


--Writes all the class files using the global table 'classes'
function writeClasses( )
	for struct,class in pairs(classes) do
		if class.hasMethods then
			if k == "cpSpatialIndex" then
				class.text = class.text:gsub("dynamicIndex", "index->dynamicIndex")--TODO
			end
			if type(class.parent) == "table" then
				table.insert(class.includes, "#include \""..class.parent.name..".hpp\"\n")
			end
			local className = struct:sub(3)
			local outName = className..".hpp"

			writeFile(outFolder.."include/"..outName, "#pragma once\n\n"..class:make())

			class:addIncludesFrom(class.body)
			class:addIncludesFrom(class.anonymousDefinitions)
			local cppFileText = "#include \""..outName.."\"\n"
			cppFileText = cppFileText..class:makeIncludes()

			cppFileText = cppFileText..class:makeAnonymousDeclarations()

			cppFileText = cppFileText.."namespace "..namespace.." {\n\n"
			cppFileText = cppFileText..class:makeMethodDefinitions()
			cppFileText = cppFileText.."};//namespace "..namespace.."\n"

			cppFileText = cppFileText..class:makeAnonymousDefinitions()

			writeFile(outFolder.."src/"..outName:gsub("hpp$", "cpp"), cppFileText)
		end
	end
end

--Compares the text with what is already there to determine if we need to update it
function writeFile( filename, text )
	local f = io.open(filename)
	local previousText = nil
	if f then
		previousText = f:read("*all")
		previousText = previousText:gsub("/*.+*/\n", "")
		f:close()
	end
	if previousText ~= text then
		text = timestamp..text
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
	local func = (lpeg.P"static " * lpeg.P"inline ")^0 *  lpeg.C(("const " + lpeg.P"") * allowed^1 * lpeg.S" *"^0) *
			lpeg.C(allowed^1) * space^0 * lpeg.S"(" * space^0 * makeArgumentPattern() * space^0 * lpeg.S")"
	return func
end


---------------------------------------
--Patterns
local beginComment = lpeg.P"//"
local endCommment = lpeg.P"\n"
local notEndComment = (1 - endCommment)^0
local commentPattern = beginComment * notEndComment * endCommment
local structPattern = "struct" * space^1 * lpeg.C(allowed^1) *((space^1 * allowed^1 * ";") + (space^0 * "{"))
local propertyPattern = "\n" * space^0 * lpeg.P"CP_" * lpeg.C(lpeg.P"Define" + lpeg.P"Declare") * lpeg.C(allowed^1) 
	* space^0 * "(" 
	* space^0 * lpeg.C((allowed + "*")^1) * space^0 * ","
	* space^0 * lpeg.C((allowed + lpeg.S"())")^1) * space^0 * ","
	* space^0 * lpeg.C(allowed^1)
	* ((space^0 * "," * space^0 * lpeg.C(allowed^1)) + "")

local typedefPattern = lpeg.C(commentPattern^0) * "typedef" * space^1 * lpeg.C(allowed^1 * space^0 * lpeg.P"*"^0) * space^0 * "("
	* space^0 * "*" * space^0 * lpeg.C(allowed^1) * space^0 * ")" * space^0 * "("
	* makeArgumentPattern() * ")" * space^0 * ";"

local functionPattern = lpeg.C(commentPattern^0) * makeFunctionPattern()

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

function getNamespace( )
	if not namespace or namespace == "" then return "" end
	return namespace.."::"
end

Method = {}
Method.__index = Method
--{ returnType=returnType, name=methodName, body=body, parameters=argTable}
function Method:new( tab )
	assert(type(tab.returnType) == "string", "returnType must be a string")
	assert(type(tab.name) == "string", "name must be a string")
	assert(type(tab.body) == "string", "body must be a string")
	assert(type(tab.parameters) == "table", "parameters must be a string")

	setmetatable(tab, self)
	return tab
end

function Method:makeDeclaration()
	local out = "\t"..self.returnType..self.name.."(".. makeRawParameters(self.parameters, true)..")"
	if self.inline then
		out = out..self:makeMethodBody()
	else
		out = out..";\n"
	end
	if self.comment then
		out = self.comment..out
	end
	return out
end

function Method:makeDefinition( )
	if self.inline then return "" end

	local out = self.returnType..self.class.name.."::"..self.name.."("..makeRawParameters(self.parameters)..")\n"
	if self.initializerList and #self.initializerList > 0 then
		for _,v in ipairs(self.initializerList) do
			if _ == 1 then
				out = out.."\t: "..v.lvalue.."("..v.rvalue.."),\n"
			else
				out = out.."\t  "..v.lvalue.."("..v.rvalue.."),\n"
			end
		end
		if out:sub(#out-1) == ",\n" then
			out = out:sub(1, #out-2).."\n"
		end
	end
	out = out..self:makeMethodBody()
	return out
end

function Method:makeMethodBody()
	return "{\n\t\t"..self.body.."}\n"
end

function Method:makeMethod()
	return self:makeDeclaration().."\n"..self:makeMethodBody()
end

function makeFunctionBody(body)
	return "\t{\n\t\t"..body.."\t}\n\n"
end



Class = {}
Class.__index = Class
function Class:new(tab)
	local structName = tab.structName


	tab.name =  tab.name or ""
	tab.text =  tab.text or ""
	tab.member =  tab.member or ""
	tab.members =  tab.members or {}
	tab.hasMethods =  tab.hasMethods
	tab.includes =  tab.includes or {}
	tab.additionalText =  tab.additionalText or ""
	tab.anonymousDeclarations =  tab.anonymousDeclarations or ""
	tab.anonymousDefinitions =  tab.anonymousDefinitions or ""
	tab.hasDataPointer =  tab.hasDataPointer
	tab.constructors =  tab.constructors or ""
	tab.parent =  tab.parent



	tab.methods = tab.methods or {}
	for k,v in pairs(tab.methods) do
		v.class = tab
	end
	setmetatable(tab, self)
	return tab
end

function Class:addMethod(method)
	self.methods.n = self.methods.n or 0
	self.methods.n = self.methods.n + 1
	table.insert(self.methods, method)
	method.class = self
end

function Class:make( )
	local out = self:makeIncludes()
	self.body = self:makeClassBody()
	out = out.."namespace "..namespace.." {\n"
	out = out..self.additionalText.."\n"
	out = out..self.body

	out = out.."};//namespace "..namespace.."\n"
	return out
end

function Class:makeMethodDefinitions( )
	local out = ""
	for _,method in ipairs(self.methods) do
		out = out..method:makeDefinition()
	end
	return out
end

function Class:makeClassBody( )
	local out = "class "..self.name
	if type(self.parent) == "string" then 
		out = out.." : public "..self.parent
	elseif self.parent then
		out = out.." : public "..self.parent.name
	end
	out = out.." {\n"
	out = out.."protected:\n"
	if self.members then
		for _,member in ipairs(self.members) do
			out = out.."\t"..member.type.." "..member.name..";\n"
		end
	end
	out = out.."public:\n"

	for _, method in ipairs(self.methods) do
		out = out..method:makeDeclaration()
	end

	out = out.."\n"
	out = out.."};\n"
	return out
end

function Class:makeAnonymousDeclarations()
	if not self.anonymousDeclarations or self.anonymousDeclarations == ""  then return "" end
	return "class "..self.name..";\n".."namespace {\n"..self.anonymousDeclarations.."}\n\n"
end

function Class:makeAnonymousDefinitions()
	if not self.anonymousDefinitions or self.anonymousDefinitions == ""  then return "" end
	return "namespace {\n"..self.anonymousDefinitions.."}\n\n"
end

function Class:addIncludesFrom( text )
	for k,v in pairs(classes) do 
		if text:find(namespace.."::"..v.name) and v.hasMethods then
			self.includes[v.name] = "#include \""..v.name..".hpp\"\n"
		end
	end
end

function Class:makeIncludes()
	local out = ""
	for includeClass, includeText in pairs(self.includes) do
		if type(includeText) == "string" then 
			out = out..includeText
		else
			out = out.."#include \""..includeClass..".hpp\"\n"
		end
	end
	return out.."\n"
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
function makeRawParameters(tab,default )
	local out = ""
	for k,v in ipairs(tab) do
		if not v.name then v.name = "" end
		if default and v.default then
			out = out..v["type"]..v["name"].." = "..v.default..","
		else
			out = out..v["type"]..v["name"]..","
		end
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
		local rawStruct = toRawStruct(v.type)
		if classes[rawStruct] and classes[rawStruct].hasMethods then 
			if v.name == classes[rawStruct].member then
				if type(classes[rawStruct].parent) == "table" then
					out = out..classes[rawStruct].parent.name.."::get(),"
				else
					out = out.."get(),"
				end
			elseif v.name == "" then
				out = out.."get(),"
			elseif v.type:find(toClass("cpBB")) or v.type:find(toClass("cpVect")) then
				out = out..v.name..","
			else
				out = out..v.name.." ? "..v.name.."->get() : 0,"
			end
		else
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




function toCppTypes( tab )
	for _,v in ipairs(tab) do
		if classes[toRawStruct(v.type)] and classes[toRawStruct(v.type)].hasMethods then
			v.type = toClass(v.type) --:gsub("%s*%*%s*", "& ")
		end
	end
end

function addGetCall( tab,struct )
	for k,v in ipairs(tab) do
		local rawStruct = toRawStruct(v.type)
		if classes[rawStruct] and classes[rawStruct].hasMethods then
			if classes[struct] and type(classes[struct].parent) == "table" and v.type:find(classes[struct].parent.structName) then
				v.name = classes[struct].parent.name.."::get()"
			elseif v.name == classes[struct].member then
				v.name = "get()"
			elseif v.type:find("cpBB") or v.type:find("cpVect") or v.type:find("cp::BB") or v.type:find("cp::Vect")then
				
			else
				v.name = v.name.." ? "..v.name.."->get() : 0"
			end
		elseif struct and (v.type:find(struct)or v.type:find(toClass(struct))) 
			and (v.type:find("cpBB") or v.type:find("cpVect") or v.type:find("cp::BB") or v.type:find("cp::Vect")) and k == 1 then
			v.name = "*this"
		end
	end
end

function firstArg( argTable, struct)
	if struct and argTable[1].type:find(struct) then
		if classes[struct].member and classes[struct].member ~= "" then
			argTable[1].name = classes[struct].member
		else 
			argTable[1].name = "*this"
		end
	end
end

--The standard function that creates a method for c++
--This should be able to handle 90% of all chipmunk methods
function makeCppMethod(returnType, functionName, argTable )

	local returnIfNotVoid = returnType:find("void%s*%**") and "" or "return "
	local methodName, struct = getMethod(functionName)
	local returnStruct = toRawStruct(returnType) --We need the struct without it being a pointer to check if it is a type we have a class for
	
	if returnIfNotVoid ~= "" and classes[returnStruct] and classes[returnStruct].hasMethods and struct then 
		returnType = toClass(returnType)
	end

	local tab = copyTable(argTable)

	if tab[1] and classes[struct] then
		if tab[1].type:find( struct) then
			tab[1].name = classes[struct].member
		end
	end

	addGetCall(tab, struct)
	firstArg(tab, struct)
	local argString = makeRawArguments(tab, struct, true)
	table.remove(tab, 1)
	table.remove(argTable, 1)
	toCppTypes(argTable)

	
	local body = functionName.."("..argString..")"

	if returnIfNotVoid ~= "" and classes[returnStruct] and struct 
		and classes[struct].hasDataPointer and returnType:find("%*") then
		body = returnType:gsub("^.*::", "cp").." temp = "..body..";\n"
		body = body.."\t\treturn static_cast<"..returnType..">(temp ? temp->data : 0);\n"
	else
		body = returnIfNotVoid..body..";\n"
	end

	return Method:new({ returnType=returnType, name=methodName, body=body, parameters=argTable}), struct
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

		local includes = {
			"#include \"chipmunk.h\"\n",
			"#include \"chipmunk_declarations.hpp\"\n" 
		}

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

		local members = {
			{name=chipmunkMember, type=structName..pointer}
		}
		if hasDataPointer then
			table.insert(members, {name="data", type="cpDataPointer"})
		end
		if structName == "cpSpace" then --We add a cp::Body* as well for the static body
			table.insert(members, {name="body", type=namespace.."::Body*"})
		end
		if structName == "cpBody" then
			table.insert(members, {name=namespace.."::Space;\n", type="friend class "})
		end

		local hasMethods = text:find("%w+%s*"..structName.."[_%w]+%s*%(")
		--Construct from a pointer to a cpStruct
		




		local methods ={
		Method:new({		
				name="get",
				body="return "..chipmunkMember..";\n",
				returnType=structName..pointer.." ",
				parameters= {type="void", name=""}
			})
		}

		local c = Class:new({
			structName=structName, 
			name=className, 
			member=chipmunkMember, 
			members=members, 
			includes=includes,
			hasMethods=hasMethods, 
			hasDataPointer=hasDataPointer, 
			constructors=constructors,
			methods=methods 
			})
		classes[structName] = c
		return e
	end)

	matchAll(typedefPattern, text,
		function ( b, comment, returnType, name, argTable,e)
			functionTypedefs[name] = {
				comment=comment,
				returnType= returnType,
				args=argTable
			}
			return e
		end)

	if not classes["cpVect"] then
		local includes = {
			"#include \"chipmunk.h\"\n"
		}
		classes["cpVect"] = Class:new(
			{structName="cpVect", name="Vect", text=classText,
			member="", hasMethods=true,
			includes=includes,
			additionalText="", anonymousDefinitions="",
			anonymousDeclarations="",
			parent="cpVect"
		})
	end

	if classes.cpBB and not classes.cpBB.parent then
		classes.cpBB.parent = "cpBB"
		classes.cpBB.member = ""
		classes.cpBB.members = nil
		classes.cpBB:addMethod(	Method:new({		
				name="BB",
				body="l = v.l; t = v.t; r = v.r; b = v.b;\n",
				returnType="",
				parameters= {{type="const cpBB ", name="v"}}
			}))
		for k,v in ipairs(classes.cpBB.methods) do 
			if v.name == "get" then
				table.remove(classes.cpBB.methods, k)
				break
			end
		end
	end

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
		function (b, comment, returnType, functionName, tab, e)
		if b then
			local _, struct = getMethod(functionName)
			if struct and classes[struct] then
				classes[struct].hasMethods = true
			end

			local method, struct = nil, nil
			for _,hook in ipairs(functionHooks) do
				method, struct = hook(returnType, functionName, tab)
				if method then break end
			end

			if not method then
				method, struct = makeCppMethod(returnType, functionName, tab)
			end

			--assert(struct == cppStruct)
			if struct and getmetatable(method) == Method then
				method.comment = comment
				classes[struct].hasMethods = true
				classes[struct]:addMethod(method)
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

			if getter then
				local body = "return cp"..class.."Get"..name.."("..structMember..");\n"
				local rawStruct = toRawStruct(structType)
				local returnType = type

				if classes[rawStruct] and classes[rawStruct].hasDataPointer then
					returnType = toClass(rawStruct).."*"
					local f = "cp"..class.."Get"..name.."("..structMember..")"
					body = rawStruct.." *temp = "..f..";\n"
					body = body.."\t\treturn static_cast<"..returnType..">(temp ? temp->data : 0);\n"
				elseif rawStruct == "cpDataPointer" then
					body = "return data;\n"
				elseif returnType == "cpVect" or returnType == "cpBB" then
					returnType = toClass(returnType)
				end

				local m = Method:new({ 
					returnType=returnType.." ", 
					name="get"..name, 
					body=body, 
					parameters={
						{name="", type="void"}
					}
				})
				classes["cp"..class]:addMethod(m)
			end
			if setter then
				local body = "cp"..class.."Set"..name.."("..structMember..",value);\n"

				if classes[toRawStruct(type)] then
					type = toClass(type)
				elseif toRawStruct(type) == "cpDataPointer" then
					body = "data = value;\n"
				end
				local m = Method:new({ 
					returnType="void ", 
					name="set"..name, 
					body=body, 
					parameters={
						{name="value", type=type.." "}
					}
				})
				classes["cp"..class]:addMethod(m)
			end
			classes["cp"..class].hasMethods = true
			return e
		end)

end


parseDir(chipmunkPath, recursive)