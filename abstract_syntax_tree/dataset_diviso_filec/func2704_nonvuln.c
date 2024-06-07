  inline THD *get_thd() const
  { return likely(table) ? table->in_use : current_thd; }