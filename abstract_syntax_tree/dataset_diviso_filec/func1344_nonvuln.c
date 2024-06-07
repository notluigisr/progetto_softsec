void Item_in_optimizer::cleanup()
{
  DBUG_ENTER("STR");
  Item_bool_func::cleanup();
  if (!save_cache)
    cache= 0;
  expr_cache= 0;
  DBUG_VOID_RETURN;
}