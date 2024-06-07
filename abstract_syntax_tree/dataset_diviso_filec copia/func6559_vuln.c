build_state (int s, struct dfa *d)
{
  int *trans;			
  int i;

  
  if (d->trcount >= 1024)
    {
      for (i = 0; i < d->tralloc; ++i)
        {
          free(d->trans[i]);
          free(d->fails[i]);
          d->trans[i] = d->fails[i] = NULL;
        }
      d->trcount = 0;
    }

  ++d->trcount;

  
  d->success[s] = 0;
  if (ACCEPTS_IN_CONTEXT(d->states[s].context, CTX_NEWLINE, s, *d))
    d->success[s] |= CTX_NEWLINE;
  if (ACCEPTS_IN_CONTEXT(d->states[s].context, CTX_LETTER, s, *d))
    d->success[s] |= CTX_LETTER;
  if (ACCEPTS_IN_CONTEXT(d->states[s].context, CTX_NONE, s, *d))
    d->success[s] |= CTX_NONE;

  MALLOC(trans, NOTCHAR);
  dfastate(s, d, trans);

  
  for (i = 0; i < NOTCHAR; ++i)
    if (trans[i] >= d->tralloc)
      {
        int oldalloc = d->tralloc;

        while (trans[i] >= d->tralloc)
          d->tralloc *= 2;
        REALLOC(d->realtrans, d->tralloc + 1);
        d->trans = d->realtrans + 1;
        REALLOC(d->fails, d->tralloc);
        REALLOC(d->success, d->tralloc);
        REALLOC(d->newlines, d->tralloc);
        while (oldalloc < d->tralloc)
          {
            d->trans[oldalloc] = NULL;
            d->fails[oldalloc++] = NULL;
          }
      }

  
  d->newlines[s] = trans[eolbyte];
  trans[eolbyte] = -1;

  if (ACCEPTING(s, *d))
    d->fails[s] = trans;
  else
    d->trans[s] = trans;
}