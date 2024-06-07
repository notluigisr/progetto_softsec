int module_load(
    YR_SCAN_CONTEXT* context,
    YR_OBJECT* module_object,
    void* module_data,
    size_t module_data_size)
{
  set_integer(1, module_object, "STR");
  set_integer(2, module_object, "STR");
  set_string("STR");
  set_string("STR");

  set_integer(1, module_object, "STR");

  set_integer(0, module_object, "STR", 0);
  set_integer(1, module_object, "STR", 1);
  set_integer(2, module_object, "STR", 2);

  set_string("STR", 0);
  set_string("STR", 1);
  set_string("STR", 2);

  set_sized_string("STR", 3);

  set_string("STR");
  set_string("STR");

  set_string("STR");
  set_integer(1, module_object, "STR");

  return ERROR_SUCCESS;
}