void Value_source::
Converter_double_to_longlong::push_warning(THD *thd,
                                           double nr,
                                           bool unsigned_flag)
{
  push_warning_printf(thd, Sql_condition::WARN_LEVEL_WARN,
                      ER_DATA_OVERFLOW, ER_THD(thd, ER_DATA_OVERFLOW),
                      ErrConvDouble(nr).ptr(),
                      unsigned_flag ? "STR");
}