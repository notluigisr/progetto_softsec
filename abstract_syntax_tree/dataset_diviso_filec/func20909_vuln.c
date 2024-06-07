void *umm_malloc( size_t size ) {
  void *ret;

  
  if (!CHECK_POISON_ALL_BLOCKS()) {
    return NULL;
  }

  
  if (!INTEGRITY_CHECK()) {
    return NULL;
  }

  size += POISON_SIZE(size);

  ret = _umm_malloc( size );

  ret = GET_POISONED(ret, size);

  umm_account_free_blocks_cnt();

  return ret;
}