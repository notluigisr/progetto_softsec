cmp_dupitems (const void *arg_a, const void *arg_b)
{
  struct dupitem_s *a = (struct dupitem_s *)arg_a;
  struct dupitem_s *b = (struct dupitem_s *)arg_b;

  return memcmp (a->digest, b->digest, 20);
}