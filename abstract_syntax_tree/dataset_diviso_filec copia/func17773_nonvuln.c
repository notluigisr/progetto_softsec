}

void internal_set_bit(REP_SET *set, uint bit)
{
  set->bits[bit / WORD_BIT] |= 1 << (bit % WORD_BIT);