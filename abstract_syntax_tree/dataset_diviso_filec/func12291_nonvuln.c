static int ntop_rrd_graph(lua_State* vm) {
  char **calcpr;
  int i, xsize, ysize;
  double ymin, ymax;
  int status;
  int argc;
  char **argv = read_string_array(vm, 1, &argc);

  reset_rrd_state();
  status = rrd_graph(argc, argv, &calcpr, &xsize, &ysize, NULL, &ymin, &ymax);

  if(status != 0) {
    
    char *err = rrd_get_error();

    if(err != NULL && strlen(err) > 0) {
      ntop->getTrace()->traceEvent(TRACE_WARNING, "STR", __FUNCTION__, err);
    }

    free(argv);
    return(CONST_LUA_OK);
  }

  lua_pushnumber(vm, (lua_Number) xsize);
  lua_pushnumber(vm, (lua_Number) ysize);

  lua_newtable(vm);
  for(i = 0; calcpr && calcpr[i]; i++) {
    lua_pushstring(vm, calcpr[i]);
    lua_rawseti(vm, -2, i+1);
    rrd_freemem(calcpr[i]);
  }

  rrd_freemem(calcpr);
  free(argv);

  return(CONST_LUA_OK);
}