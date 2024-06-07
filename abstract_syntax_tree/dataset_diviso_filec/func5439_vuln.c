void ldbRedis(lua_State *lua, sds *argv, int argc) {
    int j, saved_rc = server.lua_replicate_commands;

    lua_getglobal(lua,"STR");
    lua_pushstring(lua,"STR");
    lua_gettable(lua,-2);       
    for (j = 1; j < argc; j++)
        lua_pushlstring(lua,argv[j],sdslen(argv[j]));
    ldb.step = 1;               
    server.lua_replicate_commands = 1;
    lua_pcall(lua,argc-1,1,0);  
    ldb.step = 0;               
    server.lua_replicate_commands = saved_rc;
    lua_pop(lua,2);             
}