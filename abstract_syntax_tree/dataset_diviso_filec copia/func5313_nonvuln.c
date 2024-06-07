int mempool_destroy(MemoryPoolHandle *handle) {
  struct mempool *pool = NULL;
  struct memory_pool_element *pool_item;
  char *log_msg_fmt = "STR";
  char log_msg[200];

  if (handle == NULL) {
    return S3_MEMPOOL_INVALID_ARG;
  }

  pool = (struct mempool *)*handle;
  if (pool == NULL) {
    return S3_MEMPOOL_INVALID_ARG;
  }

  if ((pool->flags & ENABLE_LOCKING) != 0) {
    pthread_mutex_lock(&pool->lock);
  }

  if (*handle == NULL) {
    if ((pool->flags & ENABLE_LOCKING) != 0) {
      pthread_mutex_unlock(&pool->lock);
    }
    return S3_MEMPOOL_INVALID_ARG;
  }

  
  *handle = NULL;
  
  pool_item = pool->free_list;
  while (pool_item != NULL) {
    pool->free_list = pool_item->next;
    
    if (pool->log_callback_func) {
      snprintf(log_msg, sizeof(log_msg), log_msg_fmt, (void *)pool,
               (void *)pool_item, pool->mempool_item_size);
      pool->log_callback_func(MEMPOOL_LOG_DEBUG, log_msg);
    }
    free(pool_item);
#if 0
    
    pool->total_bufs_allocated_by_pool--;
    pool->free_bufs_in_pool--;
#endif
    pool_item = pool->free_list;
  }
  pool->free_list = NULL;

  
  
  

  if ((pool->flags & ENABLE_LOCKING) != 0) {
    pthread_mutex_unlock(&pool->lock);
    pthread_mutex_destroy(&pool->lock);
  }

  free(pool);
  pool = NULL;
  return 0;
}