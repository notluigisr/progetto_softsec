void LinkResolver::resolve_invokevirtual(CallInfo& result, Handle recv,
                                          const constantPoolHandle& pool, int index,
                                          TRAPS) {

  LinkInfo link_info(pool, index, CHECK);
  Klass* recvrKlass = recv.is_null() ? (Klass*)NULL : recv->klass();
  resolve_virtual_call(result, recv, recvrKlass, link_info, true, CHECK);
}