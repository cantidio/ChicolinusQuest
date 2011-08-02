#ifndef _GORGON_LUA_
#define _GORGON_LUA_

extern "C"
{
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}
#include "lua_param.hpp"
#include "lua_return.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace Gorgon{
namespace Script
{
	class Lua
	{
		private:
			lua_State*	mState; /**<< variable that holds the state of the lua interpreter*/
			bool		mClose; /**<< variable that tells if the lua state must be closed in the destructor*/
		public:
			Lua(const std::string& pScriptName="");
			Lua(lua_State* pState);
			virtual ~Lua();
			void loadScript(const std::string& pScriptName);
			void executeString(const std::string& pValue);
			LuaReturn function
			(
				const std::string&	pFunctionName,
				const LuaParam&		pParam			= LuaParam(),
				const int&			pReturnNumber	= 0
			);
			void registerFunction(const std::string& pFunctionName,int (*pFunction)(lua_State*));
			double getNumericVar(const std::string& pVarName);
			std::string getStringVar(const std::string& pVarName);
			bool getBooleanVar(const std::string& pVarName);
			int registerUserData
			(
				const std::string& pName,
				luaL_reg pMethods[],
				luaL_reg pMetatable[]
			);
			void* getUserData(const std::string& pName, const int& pIndex = 1);
			void createUserData
			(
				const std::string& pName,
				void* pUserData,
				const int& pUserDataSize
			);
	};
}}
#endif
