is_mbc_ambiguous(OnigCaseFoldType flag, const UChar** pp, const UChar* end)
{
  const UChar* p = *pp;

  if (ONIGENC_IS_MBC_ASCII(p)) {
    (*pp)++;
    return ONIGENC_IS_ASCII_CODE_CASE_AMBIG(*p);
  }
  else {
    (*pp) += enclen(ONIG_ENCODING_UTF8, p);

    if (*p == 0xc3) {
      int c = *(p + 1);
      if (c >= 0x80) {
	if (c <= (UChar )0x9e) { 
	  if (c == (UChar )0x97) return FALSE;
	  return TRUE;
	}
	else if (c >= (UChar )0xa0 && c <= (UChar )0xbe) { 
	  if (c == (UChar )'\267') return FALSE;
	  return TRUE;
	}
        else if (c == (UChar )0x9f &&
                 (flag & INTERNAL_ONIGENC_CASE_FOLD_MULTI_CHAR) != 0) {
	  return TRUE;
        }
      }
    }
  }

  return FALSE;
}