  static void fill_prof_stats(struct GC_prof_stats_s *pstats)
  {
    pstats->heapsize_full = GC_heapsize;
    pstats->free_bytes_full = GC_large_free_bytes;
    pstats->unmapped_bytes = GC_unmapped_bytes;
    pstats->bytes_allocd_since_gc = GC_bytes_allocd;
    pstats->allocd_bytes_before_gc = GC_bytes_allocd_before_gc;
    pstats->non_gc_bytes = GC_non_gc_bytes;
    pstats->gc_no = GC_gc_no; 
#   ifdef PARALLEL_MARK
      pstats->markers_m1 = (word)GC_markers_m1;
#   else
      pstats->markers_m1 = 0; 
#   endif
    pstats->bytes_reclaimed_since_gc = GC_bytes_found > 0 ?
                                        (word)GC_bytes_found : 0;
    pstats->reclaimed_bytes_before_gc = GC_reclaimed_bytes_before_gc;
  }