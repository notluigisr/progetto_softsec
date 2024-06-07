cached_resolves_eq(cached_resolve_t *a, cached_resolve_t *b)
{
  
  assert_resolve_ok(a); 
  return !strncmp(a->address, b->address, MAX_ADDRESSLEN);
}