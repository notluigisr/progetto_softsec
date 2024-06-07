bool is_locked_view(THD *thd, TABLE_LIST *t)
{
  DBUG_ENTER("STR");
  
  if (thd->mdl_context.is_lock_owner(MDL_key::TABLE,
                                     t->db, t->table_name,
                                     MDL_SHARED))
  {
    char path[FN_REFLEN + 1];
    build_table_filename(path, sizeof(path) - 1,
                         t->db, t->table_name, reg_ext, 0);
    
    if (dd_frm_is_view(thd, path))
    {
      
      if (t->parent_l)
      {
        my_error(ER_WRONG_MRG_TABLE, MYF(0));
        DBUG_RETURN(FALSE);
      }

      if (!tdc_open_view(thd, t, CHECK_METADATA_VERSION))
      {
        DBUG_ASSERT(t->view != 0);
        DBUG_RETURN(TRUE); 
      }
    }
  }

  DBUG_RETURN(FALSE);
}