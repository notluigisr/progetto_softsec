char *redisProtocolToLuaType_Aggregate(lua_State *lua, char *reply, int atype) {
    char *p = strchr(reply+1,'\r');
    long long mbulklen;
    int j = 0;

    string2ll(reply+1,p-reply-1,&mbulklen);
    if (server.lua_client->resp == 2 || atype == '*') {
        p += 2;
        if (mbulklen == -1) {
            lua_pushboolean(lua,0);
            return p;
        }
        lua_newtable(lua);
        for (j = 0; j < mbulklen; j++) {
            lua_pushnumber(lua,j+1);
            p = redisProtocolToLuaType(lua,p);
            lua_settable(lua,-3);
        }
    } else if (server.lua_client->resp == 3) {
        
        p += 2;
        lua_newtable(lua);
        lua_pushstring(lua,atype == '%' ? "STR");
        lua_newtable(lua);
        for (j = 0; j < mbulklen; j++) {
            p = redisProtocolToLuaType(lua,p);
            if (atype == '%') {
                p = redisProtocolToLuaType(lua,p);
            } else {
                lua_pushboolean(lua,1);
            }
            lua_settable(lua,-3);
        }
        lua_settable(lua,-3);
    }
    return p;
}