transit_state_consume_1char (struct dfa *d, int s, unsigned char const **pp,
                             int *match_lens, int *mbclen, position_set *pps)
{
  int i, j;
  int s1, s2;
  int* work_mbls;
  status_transit_state rs = TRANSIT_STATE_DONE;

  
  *mbclen = (mblen_buf[*pp - buf_begin] == 0)? 1
    : mblen_buf[*pp - buf_begin];

  
  s1 = s;
  for (i = 0; i < *mbclen; i++)
    {
      s2 = s1;
      rs = transit_state_singlebyte(d, s2, (*pp)++, &s1);
    }
  
  copy(&(d->states[s1].elems), pps);

  
  if (match_lens == NULL && d->states[s].mbps.nelem != 0)
    work_mbls = check_matching_with_multibyte_ops(d, s, *pp - buf_begin);
  else
    work_mbls = match_lens;

  
  for (i = 0; i < d->states[s].mbps.nelem ; i++)
   {
      if (work_mbls[i] == *mbclen)
        for (j = 0; j < d->follows[d->states[s].mbps.elems[i].index].nelem;
             j++)
          insert(d->follows[d->states[s].mbps.elems[i].index].elems[j],
                 pps);
    }

  if (match_lens == NULL && work_mbls != NULL)
    free(work_mbls);
  return rs;
}