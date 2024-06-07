void LinkResolver::resolve_invokehandle(CallInfo& result, constantPoolHandle pool, int index, TRAPS) {
  assert(EnableInvokeDynamic, "");
  
  KlassHandle  resolved_klass;
  Symbol* method_name = NULL;
  Symbol* method_signature = NULL;
  KlassHandle  current_klass;
  resolve_pool(resolved_klass, method_name,  method_signature, current_klass, pool, index, CHECK);
  if (TraceMethodHandles) {
    ResourceMark rm(THREAD);
    tty->print_cr("STR", method_name->as_C_string(), method_signature->as_C_string());
  }
  resolve_handle_call(result, resolved_klass, method_name, method_signature, current_klass, CHECK);
}