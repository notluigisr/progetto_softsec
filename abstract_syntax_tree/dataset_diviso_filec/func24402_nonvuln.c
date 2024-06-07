join_read_next_same_or_null(READ_RECORD *info)
{
  int error;
  if ((error= join_read_next_same(info)) >= 0)
    return error;
  JOIN_TAB *tab= info->table->reginfo.join_tab;

  
  if (*tab->ref.null_ref_key)
    return -1;					
  *tab->ref.null_ref_key= 1;			
  return safe_index_read(tab);			
}