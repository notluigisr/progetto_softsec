    GC_INNER GC_bool GC_page_was_ever_dirty(struct hblk * h GC_ATTR_UNUSED)
    {
#     if defined(GWW_VDB)
        if (GC_GWW_AVAILABLE())
          return GC_gww_page_was_ever_dirty(h);
#     endif
      return(TRUE);
    }