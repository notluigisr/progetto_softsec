pwg_compare_finishings(
    _pwg_finishings_t *a,		
    _pwg_finishings_t *b)		
{
  return ((int)b->value - (int)a->value);
}