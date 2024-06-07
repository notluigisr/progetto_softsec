  SELECT_LEX *select_stack_head()
  {
    if (likely(select_stack_top))
      return select_stack[select_stack_top - 1];
    return NULL;
  }