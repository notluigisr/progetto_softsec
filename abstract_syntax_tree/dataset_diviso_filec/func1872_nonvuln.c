SELECT_LEX *LEX::exclude_last_select()
{
  return exclude_not_first_select(current_select);
}