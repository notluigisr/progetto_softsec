  static CodecStats& atomicGet(AtomicPtr& ptr, Stats::Scope& scope) {
    return *ptr.get([&scope]() -> CodecStats* {
      return new CodecStats{ALL_HTTP2_CODEC_STATS(POOL_COUNTER_PREFIX(scope, "STR"))};
    });
  }