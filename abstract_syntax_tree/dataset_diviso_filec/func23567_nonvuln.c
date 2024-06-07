void InstanceKlass::fence_and_clear_init_lock() {
  
  OrderAccess::storestore();
  java_lang_Class::clear_init_lock(java_mirror());
  assert(!is_not_initialized(), "STR");
}