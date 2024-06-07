void Item_sum::cleanup()
{
  if (aggr)
  {
    delete aggr;
    aggr= NULL;
  }
  Item_result_field::cleanup();
  const_item_cache= false;
}