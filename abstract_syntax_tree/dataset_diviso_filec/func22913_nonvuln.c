bool Field::optimize_range(uint idx, uint part)
{
  return MY_TEST(table->file->index_flags(idx, part, 1) & HA_READ_RANGE);
}