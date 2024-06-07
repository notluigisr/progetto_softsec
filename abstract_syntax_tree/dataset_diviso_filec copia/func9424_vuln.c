    void writeBytes(const void* data, int length) {
      const U8* dataPtr = (const U8*)data;
      const U8* dataEnd = dataPtr + length;
      while (dataPtr < dataEnd) {
        int n = check(1, dataEnd - dataPtr);
        memcpy(ptr, dataPtr, n);
        ptr += n;
        dataPtr += n;
      }
    }