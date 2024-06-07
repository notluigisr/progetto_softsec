Item_field::Item_field(THD *thd, Name_resolution_context *context_arg,
                       Field *f)
  :Item_ident(context_arg, f->table->s->db.str, *f->table_name, f->field_name),
   item_equal(0), no_const_subst(0),
   have_privileges(0), any_privileges(0)
{
  
  {
    if (db_name)
      orig_db_name= thd->strdup(db_name);
    if (table_name)
      orig_table_name= thd->strdup(table_name);
    if (field_name)
      orig_field_name= thd->strdup(field_name);
    
    name= (char*) orig_field_name;
  }
  set_field(f);
  with_field= 1;
}