static int ia5ncasecmp(const char *s1, const char *s2, size_t n)
{
    for (; n > 0; n--, s1++, s2++) {
        if (*s1 != *s2) {
            unsigned char c1 = (unsigned char)*s1, c2 = (unsigned char)*s2;

            
            if (c1 >= 0x41  && c1 <= 0x5A )
                c1 += 0x20;
            if (c2 >= 0x41  && c2 <= 0x5A )
                c2 += 0x20;

            if (c1 == c2)
                continue;

            if (c1 < c2)
                return -1;

            
            return 1;
        } else if (*s1 == 0) {
            
            return 0;
        }
    }

    return 0;
}