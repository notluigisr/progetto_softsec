assert_connection_edge_not_dns_pending(edge_connection_t *conn)
{
  pending_connection_t *pend;
  cached_resolve_t search;

#if 1
  cached_resolve_t *resolve;
  strlcpy(search.address, conn->_base.address, sizeof(search.address));
  resolve = HT_FIND(cache_map, &cache_root, &search);
  if (!resolve)
    return;
  for (pend = resolve->pending_connections; pend; pend = pend->next) {
    tor_assert(pend->conn != conn);
  }
#else
  cached_resolve_t **resolve;
  HT_FOREACH(resolve, cache_map, &cache_root) {
    for (pend = (*resolve)->pending_connections; pend; pend = pend->next) {
      tor_assert(pend->conn != conn);
    }
  }
#endif
}