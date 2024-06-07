Item *Item_sum_avg::copy_or_same(THD* thd)
{
  return new (thd->mem_root) Item_sum_avg(thd, this);
}