routerlist_replace(routerlist_t *rl, routerinfo_t *ri_old,
                   routerinfo_t *ri_new)
{
  int idx;
  int same_descriptors;

  routerinfo_t *ri_tmp;
  extrainfo_t *ei_tmp;
  {
    
    routerinfo_t *ri_generated = router_get_my_routerinfo();
    tor_assert(ri_generated != ri_new);
  }
  tor_assert(ri_old != ri_new);
  tor_assert(ri_new->cache_info.routerlist_index == -1);

  idx = ri_old->cache_info.routerlist_index;
  tor_assert(0 <= idx && idx < smartlist_len(rl->routers));
  tor_assert(smartlist_get(rl->routers, idx) == ri_old);

  router_dir_info_changed();
  if (idx >= 0) {
    smartlist_set(rl->routers, idx, ri_new);
    ri_old->cache_info.routerlist_index = -1;
    ri_new->cache_info.routerlist_index = idx;
    
    tor_assert( _routerlist_find_elt(rl->routers, ri_old, -1) == -1 );
  } else {
    log_warn(LD_BUG, "STR");
    routerlist_insert(rl, ri_new);
    return;
  }
  if (tor_memneq(ri_old->cache_info.identity_digest,
             ri_new->cache_info.identity_digest, DIGEST_LEN)) {
    
    rimap_remove(rl->identity_map, ri_old->cache_info.identity_digest);
  }
  ri_tmp = rimap_set(rl->identity_map,
                     ri_new->cache_info.identity_digest, ri_new);
  tor_assert(!ri_tmp || ri_tmp == ri_old);
  sdmap_set(rl->desc_digest_map,
            ri_new->cache_info.signed_descriptor_digest,
            &(ri_new->cache_info));

  if (!tor_digest_is_zero(ri_new->cache_info.extra_info_digest)) {
    sdmap_set(rl->desc_by_eid_map, ri_new->cache_info.extra_info_digest,
              &ri_new->cache_info);
  }

  same_descriptors = tor_memeq(ri_old->cache_info.signed_descriptor_digest,
                              ri_new->cache_info.signed_descriptor_digest,
                              DIGEST_LEN);

  if (should_cache_old_descriptors() &&
      ri_old->purpose == ROUTER_PURPOSE_GENERAL &&
      !same_descriptors) {
    
    signed_descriptor_t *sd = signed_descriptor_from_routerinfo(ri_old);
    smartlist_add(rl->old_routers, sd);
    sd->routerlist_index = smartlist_len(rl->old_routers)-1;
    sdmap_set(rl->desc_digest_map, sd->signed_descriptor_digest, sd);
    if (!tor_digest_is_zero(sd->extra_info_digest))
      sdmap_set(rl->desc_by_eid_map, sd->extra_info_digest, sd);
  } else {
    
    if (!same_descriptors) {
      
      sdmap_remove(rl->desc_digest_map,
                   ri_old->cache_info.signed_descriptor_digest);

      if (tor_memneq(ri_old->cache_info.extra_info_digest,
                 ri_new->cache_info.extra_info_digest, DIGEST_LEN)) {
        ei_tmp = eimap_remove(rl->extra_info_map,
                              ri_old->cache_info.extra_info_digest);
        if (ei_tmp) {
          rl->extrainfo_store.bytes_dropped +=
            ei_tmp->cache_info.signed_descriptor_len;
          extrainfo_free(ei_tmp);
        }
      }

      if (!tor_digest_is_zero(ri_old->cache_info.extra_info_digest)) {
        sdmap_remove(rl->desc_by_eid_map,
                     ri_old->cache_info.extra_info_digest);
      }
    }
    rl->desc_store.bytes_dropped += ri_old->cache_info.signed_descriptor_len;
    routerinfo_free(ri_old);
  }
#ifdef DEBUG_ROUTERLIST
  routerlist_assert_ok(rl);
#endif
}