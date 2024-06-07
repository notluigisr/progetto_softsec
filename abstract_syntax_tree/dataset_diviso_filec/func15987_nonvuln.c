Item_func_sp::init_result_field(THD *thd)
{
  LEX_STRING empty_name= { C_STRING_WITH_LEN("") };
  TABLE_SHARE *share;
  DBUG_ENTER("STR");

  DBUG_ASSERT(m_sp == NULL);
  DBUG_ASSERT(sp_result_field == NULL);

  if (!(m_sp= sp_find_routine(thd, TYPE_ENUM_FUNCTION, m_name,
                               &thd->sp_func_cache, TRUE)))
  {
    my_missing_function_error (m_name->m_name, m_name->m_qname.str);
    context->process_error(thd);
    DBUG_RETURN(TRUE);
  }

  
  
  share= dummy_table->s;
  dummy_table->alias.set("", 0, table_alias_charset);
  dummy_table->maybe_null = maybe_null;
  dummy_table->in_use= thd;
  dummy_table->copy_blobs= TRUE;
  share->table_cache_key = empty_name;
  share->table_name = empty_name;

  if (!(sp_result_field= m_sp->create_result_field(max_length, name,
                                                   dummy_table)))
  {
   DBUG_RETURN(TRUE);
  }
  
  if (sp_result_field->pack_length() > sizeof(result_buf))
  {
    void *tmp;
    if (!(tmp= thd->alloc(sp_result_field->pack_length())))
      DBUG_RETURN(TRUE);
    sp_result_field->move_field((uchar*) tmp);
  }
  else
    sp_result_field->move_field(result_buf);
  
  sp_result_field->null_ptr= (uchar *) &null_value;
  sp_result_field->null_bit= 1;
  DBUG_RETURN(FALSE);
}