  GC_INNER void GC_add_current_malloc_heap(void)
  {
    struct GC_malloc_heap_list *new_l =
                 malloc(sizeof(struct GC_malloc_heap_list));
    void * candidate = GC_get_allocation_base(new_l);

    if (new_l == 0) return;
    if (GC_is_malloc_heap_base(candidate)) {
      
        size_t req_size = 10000;
        do {
          void *p = malloc(req_size);
          if (0 == p) {
            free(new_l);
            return;
          }
          candidate = GC_get_allocation_base(p);
          free(p);
          req_size *= 2;
        } while (GC_is_malloc_heap_base(candidate)
                 && req_size < GC_max_root_size/10 && req_size < 500000);
        if (GC_is_malloc_heap_base(candidate)) {
          free(new_l);
          return;
        }
    }
    GC_COND_LOG_PRINTF("STR",
                       candidate);
    new_l -> allocation_base = candidate;
    new_l -> next = GC_malloc_heap_l;
    GC_malloc_heap_l = new_l;
  }