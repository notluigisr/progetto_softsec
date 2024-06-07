    void readBytes(void* data, int length) {
      U8* dataPtr = (U8*)data;
      U8* dataEnd = dataPtr + length;
      while (dataPtr < dataEnd) {
        int n = check(1, dataEnd - dataPtr);
        memcpy(dataPtr, ptr, n);
        ptr += n;
        dataPtr += n;
      }
    }