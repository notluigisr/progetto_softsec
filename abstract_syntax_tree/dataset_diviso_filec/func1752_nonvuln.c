void Item_in_subselect::cleanup()
{
  DBUG_ENTER("STR");
  if (left_expr_cache)
  {
    left_expr_cache->delete_elements();
    delete left_expr_cache;
    left_expr_cache= NULL;
  }
  
  first_execution= TRUE;
  pushed_cond_guards= NULL;
  Item_subselect::cleanup();
  DBUG_VOID_RETURN;
}