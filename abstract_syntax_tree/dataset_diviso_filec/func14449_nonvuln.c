Item_field::Item_field(THD *thd, Field *f)
  :Item_ident(thd, 0, NullS, *f->table_name, f->field_name),
   item_equal(0),
   have_privileges(0), any_privileges(0)
{
  set_field(f);
  
  orig_table_name= orig_field_name= "";
  with_field= 1;
}