--Hooks that are called for every function found, if they return nil then the default functions are run
--Otherwise they should return the text for the function and the name of the struct that the method should be added to
functionHooks = {
	function ( returnType, functionName, argTable  )
		if functionName == "cpBodySanityCheck" then
			return ""
		end
	end
	,
	function ( returnType, functionName, argTable  )
		if functionName == "cpSpaceRemoveCollisionHandler" then
			local methodName, struct = getMethodInfo(functionName)
			local class = classes[struct]
			table.insert(class.members, {
				type="std::unordered_map<std::pair<cpCollisionType, cpCollisionType>,CollisionHandler, HashFunctor> ",
				name="collisionHandlers"
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

			local methodName, struct = getMethodInfo(functionName)
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
					
					local typedefName = toCppType(v.type):gsub(getNamespace(), "")
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
							arg.name = "static_cast<"..toCppType(arg.type)..">("..arg.name.."->data)"
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

			toCppTypes(functionArgs)
			--remove the first paramter
			table.remove(functionArgs, 1)
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
			local _, struct = getMethodInfo(functionName)
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
			local methodName, struct = getMethodInfo(functionName)
			local argType = toRawStruct(argTable[2].type)

			for _,v in ipairs(argTable) do
				if _ ~= 1 then
					v.type = toCppType(v.type):gsub("%*%*", "*")
					v.name = "&"..v.name
				end
			end
			local body = argType.." *a_, *b_;\n"
			body = body.."\t\t"..functionName.."("..argTable[1].name..", &a_, &b_);\n"
			body = body.."\t\ta = static_cast<"..toCppType(argType).."*>(a_->data);\n"
			body = body.."\t\tb = static_cast<"..toCppType(argType).."*>(b_->data);\n"

			table.remove(argTable, 1)
			return Method:new({ returnType=returnType, name=methodName, body=body, parameters=argTable}), struct
		end
	end
	,
	function ( returnType, functionName, argTable )
		if functionName:find("Free") then
			local methodName, struct = getMethodInfo(functionName)
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
			methodName, struct = getMethodInfo(functionName)
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
		makeFirstArgThisOrMember(args, struct)

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

				local methodName, struct = getMethodInfo(functionName)
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
				add={op="+", args="const Vect& "},
				mult={op="*", args="cpFloat "},
				sub={op="-", args="const Vect& "},
				neg={op="-", args="void"},
				eql={op="==", args="const Vect& "}
			}


			local returnIfNotVoid = returnType:find("void%s*%**") and "" or "return "
			if classes[toRawStruct(returnType)] then
				returnType = toCppType(returnType)
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
			local const = true

			if operatorMap[methodName] then
				local op = operatorMap[methodName]
				methodName = "operator"..op.op
				if argTable[1] then
					argTable[1].type = op.args
				end
				body = returnIfNotVoid..functionName.."("..argString..");\n"
			elseif methodName ~= "" then
				body = returnIfNotVoid..functionName.."("..argString..");\n"
			else --Methodname is "" meaning it is the constructor 'cpv'
				
				const = false
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
				classes[struct]:addMethod(Method:new({ 
					returnType="", 
					name="Vect", 
					body="this->x = cv.x; this->y = cv.y;\n", 
					parameters={{type="const cp::Vect& ", name="cv"}}
					}))

			end

			return Method:new({ 
				returnType=returnType, 
				name=methodName, 
				body=body, 
				parameters=argTable,
				const=const})
			, struct
		end
	end
	,
	function (returnType, functionName, argTable )
		if functionName:find("DataPointer") then
			local methodName, struct = getMethodInfo(functionName)
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