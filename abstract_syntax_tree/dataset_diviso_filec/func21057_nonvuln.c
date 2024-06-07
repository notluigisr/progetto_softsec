bool Item::check_type_can_return_int(const char *opname) const
{
  const Type_handler *handler= type_handler();
  if (handler->can_return_int())
    return false;
  my_error(ER_ILLEGAL_PARAMETER_DATA_TYPE_FOR_OPERATION, MYF(0),
           handler->name().ptr(), opname);
  return true;
}