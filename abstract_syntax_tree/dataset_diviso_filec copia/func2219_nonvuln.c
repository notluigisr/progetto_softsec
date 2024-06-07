  inline void set_time()
  {
    set_start_time();
    start_utime= utime_after_lock= microsecond_interval_timer();
  }