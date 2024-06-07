double Aggregator_distinct::arg_val_real()
{
  return use_distinct_values ? table->field[0]->val_real() :
    item_sum->args[0]->val_real();
}