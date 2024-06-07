GC_INNER void GC_freehblk(struct hblk *hbp)
{
    struct hblk *next, *prev;
    hdr *hhdr, *prevhdr, *nexthdr;
    word size;

    GET_HDR(hbp, hhdr);
    size = HBLKSIZE * OBJ_SZ_TO_BLOCKS(hhdr->hb_sz);
    if ((signed_word)size <= 0)
      ABORT("STR");
      
      
      
    GC_remove_counts(hbp, size);
    hhdr->hb_sz = size;
#   ifdef USE_MUNMAP
      hhdr -> hb_last_reclaimed = (unsigned short)GC_gc_no;
#   endif

    
      if (HBLK_IS_FREE(hhdr)) {
        ABORT_ARG1("STR",
                   "STR", (void *)hbp);
      }

    GC_ASSERT(IS_MAPPED(hhdr));
    hhdr -> hb_flags |= FREE_BLK;
    next = (struct hblk *)((ptr_t)hbp + size);
    GET_HDR(next, nexthdr);
    prev = GC_free_block_ending_at(hbp);
    
      if(0 != nexthdr && HBLK_IS_FREE(nexthdr) && IS_MAPPED(nexthdr)
         && (signed_word)(hhdr -> hb_sz + nexthdr -> hb_sz) > 0
         ) {
        GC_remove_from_fl(nexthdr);
        hhdr -> hb_sz += nexthdr -> hb_sz;
        GC_remove_header(next);
      }
    
      if (0 != prev) {
        prevhdr = HDR(prev);
        if (IS_MAPPED(prevhdr)
            && (signed_word)(hhdr -> hb_sz + prevhdr -> hb_sz) > 0) {
          GC_remove_from_fl(prevhdr);
          prevhdr -> hb_sz += hhdr -> hb_sz;
#         ifdef USE_MUNMAP
            prevhdr -> hb_last_reclaimed = (unsigned short)GC_gc_no;
#         endif
          GC_remove_header(hbp);
          hbp = prev;
          hhdr = prevhdr;
        }
      }
    
    
    

    GC_large_free_bytes += size;
    GC_add_to_fl(hbp, hhdr);
}