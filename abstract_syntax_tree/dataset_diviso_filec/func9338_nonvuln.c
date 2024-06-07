int InstanceKlass::vtable_index_of_interface_method(Method* intf_method) {
  assert(is_linked(), "STR");
  assert(intf_method->method_holder()->is_interface(), "STR");
  assert(is_subtype_of(intf_method->method_holder()), "STR");

  int vtable_index = Method::invalid_vtable_index;
  Symbol* name = intf_method->name();
  Symbol* signature = intf_method->signature();

  
  if (!intf_method->is_abstract() && default_methods() != NULL) {
    int index = find_method_index(default_methods(),
                                  name, signature,
                                  Klass::OverpassLookupMode::find,
                                  Klass::StaticLookupMode::find,
                                  Klass::PrivateLookupMode::find);
    if (index >= 0) {
      vtable_index = default_vtable_indices()->at(index);
    }
  }
  if (vtable_index == Method::invalid_vtable_index) {
    
    klassVtable vt = vtable();
    vtable_index = vt.index_of_miranda(name, signature);
  }
  return vtable_index;
}