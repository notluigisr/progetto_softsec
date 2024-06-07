bool LEX::sp_for_loop_condition(THD *thd, const Lex_for_loop_st &loop)
{
  Item_splocal *args[2];
  for (uint i= 0 ; i < 2; i++)
  {
    sp_variable *src= i == 0 ? loop.m_index : loop.m_target_bound;
    args[i]= new (thd->mem_root)
              Item_splocal(thd, &sp_rcontext_handler_local,
                           &src->name, src->offset, src->type_handler());
    if (unlikely(args[i] == NULL))
      return true;
#ifdef DBUG_ASSERT_EXISTS
    args[i]->m_sp= sphead;
#endif
  }

  Item *expr= loop.m_direction > 0 ?
    (Item *) new (thd->mem_root) Item_func_le(thd, args[0], args[1]) :
    (Item *) new (thd->mem_root) Item_func_ge(thd, args[0], args[1]);
  return unlikely(!expr) || unlikely(sp_while_loop_expression(thd, expr));
}