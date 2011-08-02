#ifndef _GORGON_LUA_RETURN_
#define _GORGON_LUA_RETURN_
extern "C"
{
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}
#include <iostream>
#include <string>
#include <vector>
#include "lua_argument.hpp"

namespace Gorgon{
namespace Script
{
	class LuaReturn
	{
		private:
			std::vector<LuaArgument> mArgs;
		public:
			LuaReturn(lua_State* pState,const int& pVarNumber=1);
			double getNumericValue(const int& pPos=0) const;
			std::string getStringValue(const int& pPos=0) const;
			bool getBoolValue(const int& pPos=0) const;
			int getSize() const;
	};
}}
#endif
