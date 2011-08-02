#ifndef _GORGON_LUA_PARAM_
#define _GORGON_LUA_PARAM_
extern "C"
{
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}
#include "lua_argument.hpp"
#include <string>
#include <vector>

namespace Gorgon{
namespace Script
{
	class LuaParam
	{
		private:
			std::vector<LuaArgument> mArgs;
		public:
			LuaParam();
			LuaParam(const std::string& pDesc, ...);
			void push(const double& pArg);
			void push(const std::string& pArg);
			void push(const bool& pArg);
			void pushAll(lua_State* pState) const;
			int getSize() const;
	};
}}
#endif

