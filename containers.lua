
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
	local out = "\t".. (self.inline and "inline " or "")
	out = out..self.returnType..self.name.."(".. makeRawParameters(self.parameters, true)..")"
	if self.const then
		out = out.. " const"
	end
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

	local out = self.returnType..self.class.name.."::"..self.name.."("..makeRawParameters(self.parameters)..")"
	if self.const then
		out = out.." const"
	end
	out = out.."\n"
	
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


function Class:addMoveConstructor()
	local initializerList = {}

	if self.members then
		for _,member in ipairs(self.members) do
			if member.type:find("%*") or member.type == "cpDataPointer" then
				table.insert(initializerList,{
					lvalue=member.name,
					rvalue="o."..member.name
					})
			else
				table.insert(initializerList,{
					lvalue=member.name,
					rvalue="std::move(o."..member.name..")"
					})
			end
		end
		if self.parent then
			table.insert(initializerList,{
				lvalue=self:getParentName(),
				rvalue="std::move(o)"
				})
		end
	end
	local body = ""
	if self.members then
		for _,member in ipairs(self.members) do
			if member.type:find("%*") or member.type == "cpDataPointer" then
				body = body.."\t\to."..member.name.." = 0;\n"
			end
		end
	end
	out = out.."\t}\n"

	self:addMethod(Method:new({
			returnType="", name=self.name, 
			body=body, parameters={{name="o", type=self.name.."&&"}},
			initializerList=initializerList
		}))
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

	if self.name == "Body" then
		out = out.."friend class Space;\n"
	end

	out = out.."protected:\n"
	if self.members then
		for _,member in ipairs(self.members) do
			out = out.."\t"..member.type.." "..member.name..";\n"
		end
	end
	out = out.."public:\n"

	self:addMoveConstructor()

	for _, method in ipairs(self.methods) do
		out = out..method:makeDeclaration()
	end

	out = out.."private:\n"
	out = out.."//Hiding copy constructor and assignment\n"
	if self.name ~= "Vect" and self.name ~= "BB" then
		out = out..self.name.."(const "..self.name.."&);\n"
		out = out..self.name.."& operator=(const "..self.name.."&);\n"
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

function Class:getParentName()
	if type(self.parent) == "string" then 
		return self.parent
	elseif self.parent then
		return self.parent.name
	end
end