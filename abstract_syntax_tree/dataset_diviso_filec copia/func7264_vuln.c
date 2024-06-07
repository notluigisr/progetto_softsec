  bool is_item_tree_change_register_required()
  {
    return !stmt_arena->is_conventional()
           || stmt_arena->type() == Query_arena::TABLE_ARENA;
  }