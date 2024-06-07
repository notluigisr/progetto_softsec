bool Item_singlerow_subselect::fix_length_and_dec()
{
  if ((max_columns= engine->cols()) == 1)
  {
    if (engine->fix_length_and_dec(row= &value))
      return TRUE;
  }
  else
  {
    if (!(row= (Item_cache**) current_thd->alloc(sizeof(Item_cache*) *
                                                 max_columns)) ||
        engine->fix_length_and_dec(row))
      return TRUE;
    value= *row;
  }
  unsigned_flag= value->unsigned_flag;
  
  if (engine->no_tables())
    maybe_null= engine->may_be_null();
  else
  {
    for (uint i= 0; i < max_columns; i++)
      row[i]->maybe_null= TRUE;
  }
  return FALSE;
}