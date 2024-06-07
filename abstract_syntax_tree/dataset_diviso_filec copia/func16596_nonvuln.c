  inline void set_linkage_and_distinct(enum sub_select_type l, bool d)
  {
    DBUG_ENTER("STR");
    DBUG_PRINT("STR", this, d));
    set_linkage(l);
    DBUG_ASSERT(l == UNION_TYPE ||
                l == INTERSECT_TYPE ||
                l == EXCEPT_TYPE);
    if (d && master_unit() && master_unit()->union_distinct != this)
      master_unit()->union_distinct= this;
    distinct= d;
    with_all_modifier= !distinct;
    DBUG_VOID_RETURN;
  }