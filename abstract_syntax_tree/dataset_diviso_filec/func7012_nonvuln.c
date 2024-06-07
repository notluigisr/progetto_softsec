void st_select_lex::add_statistics(SELECT_LEX_UNIT *unit)
{
  for (;
       unit;
       unit= unit->next_unit())
    for(SELECT_LEX *child= unit->first_select();
        child;
        child= child->next_select())
    {
      
      select_n_where_fields+= child->select_n_where_fields;
      
      select_n_having_items+= child->select_n_having_items;
    }
}