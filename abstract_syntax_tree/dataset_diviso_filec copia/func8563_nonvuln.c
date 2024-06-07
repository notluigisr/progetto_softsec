    CommandWQ(OSD *o, time_t ti, time_t si, ThreadPool *tp)
      : ThreadPool::WorkQueue<Command>("STR", ti, si, tp), osd(o) {}