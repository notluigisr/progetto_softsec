duint32 dwgReader18::checksum(duint32 seed, duint8* data, duint64 sz){
    duint64 size = sz;
    duint32 sum1 = seed & 0xffff;
    duint32 sum2 = seed >> 0x10;
    while (size != 0) {

        duint64 chunkSize = 0x15b0 < size? 0x15b0:size;
        size -= chunkSize;
        for (duint64 i = 0; i < chunkSize; i++) {
            sum1 += *data++;
            sum2 += sum1;
        }
        sum1 %= 0xFFF1;
        sum2 %= 0xFFF1;
    }
    return (sum2 << 0x10) | (sum1 & 0xffff);
}