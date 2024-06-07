bool Column_definition::check_length(uint mysql_errno, uint limit) const
{
  if (length <= limit)
    return false;
  my_error(mysql_errno, MYF(0), field_name.str, static_cast<ulong>(limit));
  return true;
}