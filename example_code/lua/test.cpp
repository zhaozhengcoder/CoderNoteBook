#include <string>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// c --> 调用lua --> add_exp --> 调用c
class ACTOR
{
public:
    int  id;
    int  exp;
    std::string lua_str;
};

struct USE_LUA_ENV
{
    ACTOR * actor_ptr;
};

// lua function 
USE_LUA_ENV g_use_lua_env;

int init_lua_env();
int lua_env_set(ACTOR * actor);
int lua_env_unset();
int addexp(lua_State* L);

int exec_buff(ACTOR * actor)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // 将指定的函数注册为Lua的全局函数变量，其中第一个字符串参数为Lua代码
    // 在调用C函数时使用的全局函数名，第二个参数为实际C函数的指针。
    lua_register(L, "addexp", addexp);

    lua_env_set(actor);

    // 在注册完所有的C函数之后，即可在Lua的代码块中使用这些已经注册的C函数了。
    if (luaL_dostring(L, actor->lua_str.c_str()))
    {
        printf("Failed to invoke.\n");
    }

    lua_env_unset();
    lua_close(L);
    printf("actor exec lua buff end \n");
    return 0;
}

int main()
{
    ACTOR * actor = new ACTOR();
    actor->lua_str = "addexp(100)";
    actor->exp = 5;
    actor->id = 10000;

    exec_buff(actor);
    return 0;
}

int init_lua_env()
{
    memset(&g_use_lua_env, 0, sizeof(g_use_lua_env));
    return 0;
}

int lua_env_set(ACTOR * actor)
{
    g_use_lua_env.actor_ptr = actor;
}

int lua_env_unset()
{
    g_use_lua_env.actor_ptr = 0;
}

int addexp(lua_State* L)
{
    int exp = luaL_checknumber(L,1);

    ACTOR * actor = g_use_lua_env.actor_ptr;
    if (actor == NULL) {return -1;}

    actor->exp += exp;
    printf("id %d, add exp %d, cur exp %d\n", actor->id, exp, actor->exp);
    return 0;
}