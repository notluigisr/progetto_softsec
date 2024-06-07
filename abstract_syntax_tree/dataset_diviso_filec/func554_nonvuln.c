    GC_INNER GC_bool GC_gww_dirty_init(void)
    {
      detect_GetWriteWatch();
      return GC_GWW_AVAILABLE();
    }