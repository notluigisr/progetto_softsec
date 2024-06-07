build_collating_symbol (bitset_t sbcset, const unsigned char *name)
# endif 
{
  size_t name_len = strlen ((const char *) name);
  if (BE (name_len != 1, 0))
    return REG_ECOLLATE;
  else
    {
      bitset_set (sbcset, name[0]);
      return REG_NOERROR;
    }
}