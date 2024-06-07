Field *Field_decimal::make_new_field(MEM_ROOT *root, TABLE *new_table,
                                     bool keep_type)
{
  if (keep_type)
    return Field_real::make_new_field(root, new_table, keep_type);

  Field *field= new (root) Field_new_decimal(NULL, field_length,
                                             maybe_null() ? (uchar*) "" : 0, 0,
                                             NONE, &field_name,
                                             dec, flags & ZEROFILL_FLAG,
                                             unsigned_flag);
  if (field)
    field->init_for_make_new_field(new_table, orig_table);
  return field;
}