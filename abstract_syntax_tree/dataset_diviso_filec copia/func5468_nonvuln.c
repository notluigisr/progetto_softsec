LUALIB_API int luaopen_cmsgpack(lua_State *L) {
    luaopen_create(L);

#if LUA_VERSION_NUM < 502
    
    lua_pushvalue(L, -1);
    lua_setglobal(L, LUACMSGPACK_NAME);
#endif

    return 1;
}