_asn1_convert_integer (const unsigned char *value, unsigned char *value_out,
		       int value_out_size, int *len)
{
  char negative;
  unsigned char val[SIZEOF_UNSIGNED_LONG_INT];
  long valtmp;
  int k, k2;

  valtmp = _asn1_strtol (value, NULL, 10);

  for (k = 0; k < SIZEOF_UNSIGNED_LONG_INT; k++)
    {
      val[SIZEOF_UNSIGNED_LONG_INT - k - 1] = (valtmp >> (8 * k)) & 0xFF;
    }

  if (val[0] & 0x80)
    negative = 1;
  else
    negative = 0;

  for (k = 0; k < SIZEOF_UNSIGNED_LONG_INT - 1; k++)
    {
      if (negative && (val[k] != 0xFF))
	break;
      else if (!negative && val[k])
	break;
    }

  if ((negative && !(val[k] & 0x80)) || (!negative && (val[k] & 0x80)))
    k--;

  *len = SIZEOF_UNSIGNED_LONG_INT - k;

  if (SIZEOF_UNSIGNED_LONG_INT - k > value_out_size)
    
    return ASN1_MEM_ERROR;

  for (k2 = k; k2 < SIZEOF_UNSIGNED_LONG_INT; k2++)
    value_out[k2 - k] = val[k2];

#if 0
  printf ("STR", value, *len);
  for (k = 0; k < SIZEOF_UNSIGNED_LONG_INT; k++)
    printf ("STR", k, value_out[k]);
  printf ("STR");
#endif

  return ASN1_SUCCESS;
}