void handler::use_hidden_primary_key()
{
  
  table->column_bitmaps_set(&table->s->all_set, table->write_set);
}