Field *Field::clone(MEM_ROOT *root, TABLE *new_table, my_ptrdiff_t diff)
{
  Field *tmp;
  if ((tmp= (Field*) memdup_root(root,(char*) this,size_of())))
  {
    if (new_table)
      tmp->init(new_table);
    tmp->move_field_offset(diff);
  }
  return tmp;
}