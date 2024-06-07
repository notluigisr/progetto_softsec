int main()
{
    uint32_t u1 = 3141592653U;      
    int32_t i1 = -1153374643;       
    uint64_t ul1 = 1099511627776LL; 
    uint64_t ul2 = 12345;           
    int32_t i2 = 81;                
    char c1 = '\xf7';               

    
    assert(static_cast<uint32_t>(i1) == u1);
    
    assert(c1 == static_cast<char>(static_cast<unsigned char>(c1)));

    try_convert(true,  QIntC::to_int<int32_t>, i1);
    try_convert(true,  QIntC::to_uint<uint32_t>, u1);
    try_convert(false, QIntC::to_int<uint32_t>, u1);
    try_convert(false, QIntC::to_uint<int32_t>, i1);
    try_convert(false, QIntC::to_int<uint64_t>, ul1);
    try_convert(true,  QIntC::to_int<uint64_t>, ul2);
    try_convert(true,  QIntC::to_uint<uint64_t>, ul2);
    try_convert(true,  QIntC::to_offset<uint32_t>, u1);
    try_convert(true,  QIntC::to_offset<int32_t>, i1);
    try_convert(false, QIntC::to_size<int32_t>, i1);
    try_convert(true,  QIntC::to_char<int32_t>, i2);
    try_convert(true,  QIntC::to_uchar<int32_t>, i2);
    try_convert(false,  QIntC::to_uchar<char>, c1);

    return 0;
}