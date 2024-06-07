void TABLE_LIST::check_pushable_cond_for_table(Item *cond)
{
  table_map tab_map= table->map;
  cond->clear_extraction_flag();
  if (cond->type() == Item::COND_ITEM)
  {
    bool and_cond= ((Item_cond*) cond)->functype() == Item_func::COND_AND_FUNC;
    List_iterator<Item> li(*((Item_cond*) cond)->argument_list());
    uint count= 0;
    Item *item;
    while ((item=li++))
    {
      check_pushable_cond_for_table(item);
      if (item->get_extraction_flag() !=  NO_EXTRACTION_FL)
        count++;
      else if (!and_cond)
        break;
    }
    if ((and_cond && count == 0) || item)
    {
      cond->set_extraction_flag(NO_EXTRACTION_FL);
      if (and_cond)
        li.rewind();
      while ((item= li++))
        item->clear_extraction_flag();
    }
  }
  else if (!cond->excl_dep_on_table(tab_map))
    cond->set_extraction_flag(NO_EXTRACTION_FL);
}