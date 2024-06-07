Field *Type_handler_enum::make_conversion_table_field(TABLE *table,
                                                      uint metadata,
                                                      const Field *target)
                                                      const
{
  DBUG_ASSERT(target->type() == MYSQL_TYPE_STRING);
  DBUG_ASSERT(target->real_type() == MYSQL_TYPE_ENUM);
  return new(table->in_use->mem_root)
         Field_enum(NULL, target->field_length,
                    (uchar *) "", 1, Field::NONE, TMPNAME,
                    metadata & 0x00ff,
                    ((const Field_enum*) target)->typelib, target->charset());
}