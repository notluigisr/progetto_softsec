  ha_rows get_rownum() const
  {
    if (io_cache)
      return rownum;
    else
      return (cache_pos - cache_start) / ref_length;
  }