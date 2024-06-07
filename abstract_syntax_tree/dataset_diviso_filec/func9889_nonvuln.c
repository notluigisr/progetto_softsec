wextglob_skipname (pat, dname, flags)
     wchar_t *pat, *dname;
     int flags;
{
#if EXTENDED_GLOB
  wchar_t *pp, *pe, *t, n, *se;
  int r, negate, wild, nullpat;

  negate = *pat == L'!';
  wild = *pat == L'*' || *pat == L'?';
  pp = pat + 2;
  se = pp + wcslen (pp) - 1;	
  pe = glob_patscan_wc (pp, se, 0);

  if (pe == se && *pe == ')' && (t = wcschr (pp, L'|')) == 0)
    {
      *pe = L'\0';
      r = wskipname (pp, dname, flags); 
      *pe = L')';
      if (wild && pe[1] != L'\0')
        return (wskipname (pe+1, dname, flags));
      return r;
    }

  
  nullpat = pe >= (pat + 2) && pe[-2] == L'(' && pe[-1] == L')';

  
  while (t = glob_patscan_wc (pp, pe, '|'))
    {
      n = t[-1];	
      if (wextglob_pattern_p (pp) && n == L')')
	t[-1] = n;	
      else
	t[-1] = L'\0';
      r = wskipname (pp, dname, flags);
      t[-1] = n;
      if (r == 0)
	return 0;
      pp = t;
    }

  if (pp == pe)		
    return r;

  
  if (wild && *pe != L'\0')
    return (wskipname (pe, dname, flags));
  return 1;
#else
  return (wskipname (pat, dname, flags));
#endif
}