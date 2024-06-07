void LinkResolver::resolve_handle_call(CallInfo& result,
                                       const LinkInfo& link_info,
                                       TRAPS) {
  
  Klass* resolved_klass = link_info.resolved_klass();
  assert(resolved_klass == vmClasses::MethodHandle_klass() ||
         resolved_klass == vmClasses::VarHandle_klass(), "");
  assert(MethodHandles::is_signature_polymorphic_name(link_info.name()), "");
  Handle resolved_appendix;
  Method* m = lookup_polymorphic_method(link_info, &resolved_appendix, CHECK);
  methodHandle resolved_method(THREAD, m);

  if (link_info.check_access()) {
    Symbol* name = link_info.name();
    vmIntrinsics::ID iid = MethodHandles::signature_polymorphic_name_id(name);
    if (MethodHandles::is_signature_polymorphic_intrinsic(iid)) {
      
      
      assert(iid == vmIntrinsicID::_invokeBasic, "STR", vmIntrinsics::name_at(iid));

      Klass* current_klass = link_info.current_klass();
      assert(current_klass != NULL , "STR");
      check_method_accessability(current_klass,
                                 resolved_klass,
                                 resolved_method->method_holder(),
                                 resolved_method,
                                 CHECK);
    } else {
      
      assert(iid == vmIntrinsics::_invokeGeneric, "STR", vmIntrinsics::name_at(iid));
      assert(MethodHandles::is_signature_polymorphic_public_name(resolved_klass, name), "STR");
    }
  }
  result.set_handle(resolved_klass, resolved_method, resolved_appendix, CHECK);
}