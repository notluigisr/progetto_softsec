assert_resolve_ok(cached_resolve_t *resolve)
{
  tor_assert(resolve);
  tor_assert(resolve->magic == CACHED_RESOLVE_MAGIC);
  tor_assert(strlen(resolve->address) < MAX_ADDRESSLEN);
  tor_assert(tor_strisnonupper(resolve->address));
  if (resolve->state != CACHE_STATE_PENDING) {
    tor_assert(!resolve->pending_connections);
  }
  if (resolve->state == CACHE_STATE_PENDING ||
      resolve->state == CACHE_STATE_DONE) {
    tor_assert(!resolve->ttl);
    if (resolve->is_reverse)
      tor_assert(!resolve->result.hostname);
    else
      tor_assert(!resolve->result.a.addr);
  }
}