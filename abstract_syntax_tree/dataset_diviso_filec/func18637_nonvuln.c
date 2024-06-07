static int ntop_get_dirs(lua_State* vm) {
  ntop->getTrace()->traceEvent(TRACE_DEBUG, "STR", __FUNCTION__);

  lua_newtable(vm);
  lua_push_str_table_entry(vm, "STR", ntop->get_install_dir());
  lua_push_str_table_entry(vm, "STR", ntop->get_working_dir());
  lua_push_str_table_entry(vm, "STR", ntop->getPrefs()->get_scripts_dir());
  lua_push_str_table_entry(vm, "STR", ntop->getPrefs()->get_docs_dir());
  lua_push_str_table_entry(vm, "STR", ntop->getPrefs()->get_callbacks_dir());

  return(CONST_LUA_OK);
}