#include "lua.hpp"
#include <string>

namespace Gorgon{
namespace Script
{
	inline std::string getErrorMsg(lua_State *L, int status)
	{
		std::string msg;
		if (status)
		{
			msg = lua_tostring(L, -1);
			if (msg.length() == 0)
			{
				msg = "(error with no message).";
			}
			return msg;
		}
		return "No Error.";
	}

	Lua::Lua(const std::string& pScriptName)
	{
		mState	= lua_open();
		mClose	= true;
		luaL_openlibs(mState);

		if(pScriptName.length())
		{
			loadScript(pScriptName);
		}
	}
	/**@todo remover esse método*/
	Lua::Lua(lua_State* pState)
	{
		mState	= pState;
		mClose	= false;
	}

	Lua::~Lua()
	{
		if(mClose)
		{
			lua_close(mState);
		}
	}

	void Lua::loadScript(const std::string& pScriptName)
	{
		if(pScriptName == "")
		{
			return;
		}
		int status = luaL_loadfile(mState, pScriptName.c_str());
		switch(status)
		{
			case 0:
				lua_pcall(mState, 0, LUA_MULTRET, 0);
				break;
			default:
				printf("Error in script: %s\n", getErrorMsg(mState, status).c_str());
				break;
		}
	}

	void Lua::executeString(const std::string& pValue)
	{
		const int status = luaL_dostring(mState, pValue.c_str());
		if(status != 0)
		{
			printf("Error in script: %s\n", getErrorMsg(mState, status).c_str());
		}
	}

	LuaReturn Lua::function
	(
		const std::string&	pFunctionName,
		const LuaParam&		pParam,
		const int&			pReturnNumber
	)
	{
		lua_getglobal(mState, pFunctionName.c_str());
		pParam.pushAll(mState);//pushing the arguments
		const int status = lua_pcall
		(
			mState,
			pParam.getSize(),
			pReturnNumber,
			0
		);
		if(status != 0) {}
		return LuaReturn(mState,pReturnNumber);
	}

	void Lua::registerFunction(const std::string& pFunctionName,int (*pFunction) (lua_State*))
	{
		lua_register
		(
			mState,
			pFunctionName.c_str(),
			pFunction
		);
	}

	double Lua::getNumericVar(const std::string& pVarName)
	{
		lua_getglobal(mState,pVarName.c_str());
		if (!lua_isnumber(mState, -1))
		{
			return 0;
		}
		return (double)lua_tonumber(mState, -1);
	}

	std::string Lua::getStringVar(const std::string& pVarName)
	{
		lua_getglobal(mState, pVarName.c_str());
		if (!lua_isstring(mState, -1))
		{
			return std::string("");
		}
		return std::string((char*)lua_tostring(mState, -1));
	}

	bool Lua::getBooleanVar(const std::string& pVarName)
	{
		lua_getglobal(mState,pVarName.c_str());
		if (!lua_isboolean(mState,-1))
		{
			return false;
		}
		return (bool)lua_toboolean(mState, -1);
	}

	int Lua::registerUserData
	(
		const std::string& pName,
		luaL_reg pMethods[],
		luaL_reg pMetatable[]
	)
	{
		if(mState != NULL)
		{
			luaL_openlib		(mState, pName.c_str(), pMethods, 0);	/* create methods table, add it to the globals */
			luaL_newmetatable	(mState, pName.c_str());				/* create metatable for UserData, add it to the Lua register */
			luaL_openlib		(mState, 0, pMetatable, 0);				/* fill metatable */
			lua_pushliteral		(mState, "__index");
			lua_pushvalue		(mState, -3);							/* dup methods table*/
			lua_rawset			(mState, -3);							/* metatable.__index = methods */
			lua_pushliteral		(mState, "__metatable");
			lua_pushvalue		(mState, -3);							/* dup methods table*/
			lua_rawset			(mState, -3);							/* hide metatable: metatable.__metatable = methods */
			lua_pop				(mState, 1);							/* drop metatable */
		}
		else
		{
			return 0;
		}
		return 1;
	}

	void* Lua::getUserData(const std::string& pName, const int& pIndex)
	{
		void** l_inst; //lua instance
		luaL_checktype(mState, pIndex, LUA_TUSERDATA);
		l_inst = (void**)luaL_checkudata(mState, pIndex, pName.c_str());
		if (l_inst == NULL)
		{
			luaL_typerror(mState, pIndex, pName.c_str());
		}
		if (!*l_inst)
		{
			luaL_error(mState, "null Vector");
		}
		return *l_inst;
	}

	void Lua::createUserData
	(
		const std::string& pName,
		void* pUserData,
		const int& pUserDataSize
	)
	{
		void** l_inst;
		l_inst	= (void**)lua_newuserdata(mState, pUserDataSize);	//create the userdata, of the size passed
		*l_inst	= pUserData;										//set the pointer to the userdata
		luaL_getmetatable	(mState, pName.c_str());
		lua_setmetatable	(mState, -2);
	}
}}
