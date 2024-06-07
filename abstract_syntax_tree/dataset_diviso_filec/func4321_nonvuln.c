void TR_table::store(uint field_id, timeval ts)
{
  table->field[field_id]->store_timestamp(ts.tv_sec, ts.tv_usec);
  table->field[field_id]->set_notnull();
}