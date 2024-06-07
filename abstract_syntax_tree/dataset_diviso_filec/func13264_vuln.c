static inline int parse_mask(NM self, const char *str, int flags) {
    char *p;
    uint32_t v;
    struct in6_addr s6;
    struct in_addr s;

    v = strtoul(str, &p, 0);
    if(*p == '\0') {
        
        if(is_v4(self)) {
            if(v < 0 || v > 32) return 0;
            v += 96;
        } else {
            if(v < 0 || v > 128) return 0;
        }
        self->mask = u128_cidr(v);
    } else if(inet_pton(AF_INET6, str, &s6)) {
        self->mask = u128_of_s6(&s6);
        
        if(u128_cmp(
            u128_lit(0, 0),
            u128_and(
                u128_lit(1ULL << 63, 1),
                u128_xor(u128_lit(0, 1), self->mask)
            )
        ) == 0) {
            self->mask = u128_neg(self->mask);
        }
        self->domain = AF_INET6;
    } else if(self->domain == AF_INET && inet_aton(str, &s)) {
        v = htonl(s.s_addr);
        if(v & 1 && ~v >> 31) 
            v = ~v;
        
        self->mask = u128_xor(self->mask, u128_lit(0, ~v));
    } else {
        return 0;
    }
    if(!chkmask(self->mask))
        return 0;
    
    self->neta = u128_and(self->neta, self->mask);
    return 1;
}