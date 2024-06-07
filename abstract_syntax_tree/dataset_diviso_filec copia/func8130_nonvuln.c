static inline uint8_t decode_sym(GetBitContext *gb, uint8_t lru[8])
{
    uint8_t c, val;

    c = get_unary(gb, 0, 8);
    if (!c) {
        val = get_bits(gb, 8);
        memmove(lru + 1, lru, sizeof(*lru) * (8 - 1));
    } else {
        val = lru[c - 1];
        memmove(lru + 1, lru, sizeof(*lru) * (c - 1));
    }
    lru[0] = val;

    return val;
}