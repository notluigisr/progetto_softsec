void LinkResolver::resolve_invokevirtual(CallInfo& result, Handle recv,
                                          constantPoolHandle pool, int index,
                                          TRAPS) {

  KlassHandle  resolved_klass;
  Symbol* method_name = NULL;
  Symbol* method_signature = NULL;
  KlassHandle  current_klass;
  resolve_pool(resolved_klass, method_name,  method_signature, current_klass, pool, index, CHECK);
  KlassHandle recvrKlass (THREAD, recv.is_null() ? (Klass*)NULL : recv->klass());
  resolve_virtual_call(result, recv, recvrKlass, resolved_klass, method_name, method_signature, current_klass, true, true, CHECK);
}