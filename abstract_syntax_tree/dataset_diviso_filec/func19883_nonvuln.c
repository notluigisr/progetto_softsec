void Item_sum_count::reset_field()
{
  uchar *res=result_field->ptr;
  longlong nr=0;
  DBUG_ASSERT (aggr->Aggrtype() != Aggregator::DISTINCT_AGGREGATOR);

  if (!args[0]->maybe_null || !args[0]->is_null())
    nr=1;
  int8store(res,nr);
}