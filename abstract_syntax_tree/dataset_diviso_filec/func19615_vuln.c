    MemInStream(const void* data, int len, bool deleteWhenDone_=false)
      : start((const U8*)data), deleteWhenDone(deleteWhenDone_)
    {
      ptr = start;
      end = start + len;
    }