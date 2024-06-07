int mutt_seqset_iterator_next(struct SeqsetIterator *iter, unsigned int *next)
{
  if (!iter || !next)
    return -1;

  if (iter->in_range)
  {
    if ((iter->down && (iter->range_cur == (iter->range_end - 1))) ||
        (!iter->down && (iter->range_cur == (iter->range_end + 1))))
    {
      iter->in_range = 0;
    }
  }

  if (!iter->in_range)
  {
    iter->substr_cur = iter->substr_end;
    if (iter->substr_cur == iter->eostr)
      return 1;

    while (!*(iter->substr_cur))
      iter->substr_cur++;
    iter->substr_end = strchr(iter->substr_cur, ',');
    if (!iter->substr_end)
      iter->substr_end = iter->eostr;
    else
      *(iter->substr_end) = '\0';

    char *range_sep = strchr(iter->substr_cur, ':');
    if (range_sep)
      *range_sep++ = '\0';

    if (mutt_str_atoui(iter->substr_cur, &iter->range_cur) != 0)
      return -1;
    if (range_sep)
    {
      if (mutt_str_atoui(range_sep, &iter->range_end) != 0)
        return -1;
    }
    else
      iter->range_end = iter->range_cur;

    iter->down = (iter->range_end < iter->range_cur);
    iter->in_range = 1;
  }

  *next = iter->range_cur;
  if (iter->down)
    iter->range_cur--;
  else
    iter->range_cur++;

  return 0;
}