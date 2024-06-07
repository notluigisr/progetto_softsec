dfaoptimize (struct dfa *d)
{
  unsigned int i;

  if (!MBS_SUPPORT || !using_utf8())
    return;

  for (i = 0; i < d->tindex; ++i)
    {
      switch(d->tokens[i])
        {
        case ANYCHAR:
          
          abort ();
        case MBCSET:
          
          return;
        default:
          break;
        }
    }

  free_mbdata (d);
  d->mb_cur_max = 1;
}