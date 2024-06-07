static int ntop_get_interface_local_hosts(lua_State* vm) {
  NetworkInterfaceView *ntop_interface = getCurrentInterface(vm);

  ntop->getTrace()->traceEvent(TRACE_INFO, "STR", __FUNCTION__);

  if(ntop_interface) ntop_interface->getActiveHostsList(vm, get_allowed_nets(vm), false, true);

  return(CONST_LUA_OK);
}