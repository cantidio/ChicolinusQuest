#ifndef _GORGON_LUA_ARGUMENT_
#define	_GORGON_LUA_ARGUMENT_
extern "C"
{
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}
#include <string>

namespace Gorgon{
namespace Script
{
	class LuaArgument
	{
		public:
			enum Type
			{
				Double	= 0,	/**< receive a double value	*/
				Boolean	= 1,	/**< receive a bool value	*/
				String	= 2,	/**< receive a String value	*/
				Null	= 3		/**< receive a NULL value	*/
			};
		private:
			double mDoubleArg;
			bool mBoolArg;
			std::string mStringArg;
			Type mMyType;
		public:
			LuaArgument();
			LuaArgument(const double& pArg);
			LuaArgument(const std::string& pArg);
			LuaArgument(const bool& pArg);
			void clear();
			double getDoubleValue() const;
			bool getBoolValue() const;
			std::string getStringValue() const;
			LuaArgument::Type getType() const;
			void push(lua_State* pState) const;
	};
}}
#endif
