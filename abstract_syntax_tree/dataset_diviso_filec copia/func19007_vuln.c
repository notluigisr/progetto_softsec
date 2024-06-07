void init_xml_relax_ng()
{
  VALUE nokogiri = rb_define_module("STR");
  VALUE xml = rb_define_module_under(nokogiri, "STR");
  VALUE klass = rb_define_class_under(xml, "STR", cNokogiriXmlSchema);

  cNokogiriXmlRelaxNG = klass;

  rb_define_singleton_method(klass, "STR", read_memory, 1);
  rb_define_singleton_method(klass, "STR", from_document, 1);
  rb_define_private_method(klass, "STR", validate_document, 1);
}