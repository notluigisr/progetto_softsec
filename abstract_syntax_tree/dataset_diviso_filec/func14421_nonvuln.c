void Item_in_optimizer::get_cache_parameters(List<Item> &parameters)
{
  DBUG_ASSERT(fixed);
  
  if (!invisible_mode())
  {
    if (args[0]->cols() == 1)
      parameters.add_unique(args[0], &cmp_items);
    else
    {
      for (uint i= 0; i < args[0]->cols(); i++)
      {
        parameters.add_unique(args[0]->element_index(i), &cmp_items);
      }
    }
  }
  args[1]->get_cache_parameters(parameters);
}