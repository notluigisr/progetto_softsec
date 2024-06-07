_compare_pairs(const void **a, const void **b)
{
  const fp_pair_t *fp1 = *a, *fp2 = *b;
  int r;
  if ((r = fast_memcmp(fp1->first, fp2->first, DIGEST_LEN)))
    return r;
  else
    return fast_memcmp(fp1->second, fp2->second, DIGEST_LEN);
}