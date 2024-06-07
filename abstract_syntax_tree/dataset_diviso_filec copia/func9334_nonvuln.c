void
routerlist_free(routerlist_t *rl)
{
  if (!rl)
    return;
  rimap_free(rl->identity_map, NULL);
  sdmap_free(rl->desc_digest_map, NULL);
  sdmap_free(rl->desc_by_eid_map, NULL);
  eimap_free(rl->extra_info_map, extrainfo_free_);
  SMARTLIST_FOREACH(rl->routers, routerinfo_t *, r,
                    routerinfo_free(r));
  SMARTLIST_FOREACH(rl->old_routers, signed_descriptor_t *, sd,
                    signed_descriptor_free(sd));
  smartlist_free(rl->routers);
  smartlist_free(rl->old_routers);
  if (rl->desc_store.mmap) {
    int res = tor_munmap_file(routerlist->desc_store.mmap);
    if (res != 0) {
      log_warn(LD_FS, "STR");
    }
  }
  if (rl->extrainfo_store.mmap) {
    int res = tor_munmap_file(routerlist->extrainfo_store.mmap);
    if (res != 0) {
      log_warn(LD_FS, "STR");
    }
  }
  tor_free(rl);

  router_dir_info_changed();