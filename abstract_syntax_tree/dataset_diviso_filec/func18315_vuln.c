static PCRE2_SPTR SLJIT_FUNC do_extuni_no_utf(jit_arguments *args, PCRE2_SPTR cc)
{
PCRE2_SPTR start_subject = args->begin;
PCRE2_SPTR end_subject = args->end;
int lgb, rgb, ricount;
PCRE2_SPTR bptr;
uint32_t c;

GETCHARINC(c, cc);
lgb = UCD_GRAPHBREAK(c);

while (cc < end_subject)
  {
  c = *cc;
  rgb = UCD_GRAPHBREAK(c);

  if ((PRIV(ucp_gbtable)[lgb] & (1 << rgb)) == 0) break;

  

  if (lgb == ucp_gbRegionalIndicator && rgb == ucp_gbRegionalIndicator)
    {
    ricount = 0;
    bptr = cc - 1;

    
    while (bptr > start_subject)
      {
      bptr--;
      c = *bptr;

      if (UCD_GRAPHBREAK(c) != ucp_gbRegionalIndicator) break;

      ricount++;
      }

    if ((ricount & 1) != 0) break;  
    }

  

  if ((rgb != ucp_gbExtend && rgb != ucp_gbZWJ) ||
       lgb != ucp_gbExtended_Pictographic)
    lgb = rgb;

  cc++;
  }

return cc;
}