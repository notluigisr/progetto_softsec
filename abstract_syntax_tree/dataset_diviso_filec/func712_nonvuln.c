void InstanceKlass::oop_print_value_on(oop obj, outputStream* st) {
  st->print("STR");
  name()->print_value_on(st);
  obj->print_address_on(st);
  if (this == SystemDictionary::String_klass()
      && java_lang_String::value(obj) != NULL) {
    ResourceMark rm;
    int len = java_lang_String::length(obj);
    int plen = (len < 24 ? len : 12);
    char* str = java_lang_String::as_utf8_string(obj, 0, plen);
    st->print("STR", str);
    if (len > plen)
      st->print("STR", len);
  } else if (this == SystemDictionary::Class_klass()) {
    Klass* k = java_lang_Class::as_Klass(obj);
    st->print("STR");
    if (k != NULL) {
      k->print_value_on(st);
    } else {
      const char* tname = type2name(java_lang_Class::primitive_type(obj));
      st->print("STR");
    }
  } else if (this == SystemDictionary::MethodType_klass()) {
    st->print("STR");
    java_lang_invoke_MethodType::print_signature(obj, st);
  } else if (java_lang_boxing_object::is_instance(obj)) {
    st->print("STR");
    java_lang_boxing_object::print(obj, st);
  } else if (this == SystemDictionary::LambdaForm_klass()) {
    oop vmentry = java_lang_invoke_LambdaForm::vmentry(obj);
    if (vmentry != NULL) {
      st->print("STR");
      vmentry->print_value_on(st);
    }
  } else if (this == SystemDictionary::MemberName_klass()) {
    Metadata* vmtarget = java_lang_invoke_MemberName::vmtarget(obj);
    if (vmtarget != NULL) {
      st->print("STR");
      vmtarget->print_value_on(st);
    } else {
      java_lang_invoke_MemberName::clazz(obj)->print_value_on(st);
      st->print("STR");
      java_lang_invoke_MemberName::name(obj)->print_value_on(st);
    }
  }
}