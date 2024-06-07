int LinkResolver::vtable_index_of_interface_method(KlassHandle klass,
                                          methodHandle resolved_method) {

  int vtable_index = Method::invalid_vtable_index;
  Symbol* name = resolved_method->name();
  Symbol* signature = resolved_method->signature();

  
  if (!resolved_method->is_abstract() &&
    (InstanceKlass::cast(klass())->default_methods() != NULL)) {
    int index = InstanceKlass::find_method_index(InstanceKlass::cast(klass())->default_methods(),
                                                 name, signature, Klass::find_overpass,
                                                 Klass::find_static, Klass::find_private);
    if (index >= 0 ) {
      vtable_index = InstanceKlass::cast(klass())->default_vtable_indices()->at(index);
    }
  }
  if (vtable_index == Method::invalid_vtable_index) {
    
    ResourceMark rm;
    klassVtable *vt = InstanceKlass::cast(klass())->vtable();
    vtable_index = vt->index_of_miranda(name, signature);
  }
  return vtable_index;
}