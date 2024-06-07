bool st_select_lex::setup_ref_array(THD *thd, uint order_group_num)
{

  if (!((options & SELECT_DISTINCT) && !group_list.elements))
    hidden_bit_fields= 0;

  
  order_group_num*= 2;

  
  Query_arena *arena= thd->stmt_arena;
  const uint n_elems= (n_sum_items +
                       n_child_sum_items +
                       item_list.elements +
                       select_n_reserved +
                       select_n_having_items +
                       select_n_where_fields +
                       order_group_num +
                       hidden_bit_fields +
                       fields_in_window_functions) * 5;
  if (!ref_pointer_array.is_null())
  {
    
    if (ref_pointer_array.size() >= n_elems)
      return false;
   }
  Item **array= static_cast<Item**>(arena->alloc(sizeof(Item*) * n_elems));
  if (array != NULL)
    ref_pointer_array= Ref_ptr_array(array, n_elems);

  return array == NULL;
}