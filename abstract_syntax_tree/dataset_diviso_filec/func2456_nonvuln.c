void MD5::init()
{
    count[0] = count[1] = 0;
    
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;

    finalized = false;
    memset(digest_val, 0, sizeof(digest_val));
}