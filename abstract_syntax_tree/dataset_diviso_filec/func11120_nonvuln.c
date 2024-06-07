  uint64_t get_osd_stat_seq() {
    Mutex::Locker l(stat_lock);
    return osd_stat.seq;
  }