static inline void expand_func(int16_t *rp, int16_t *rn,
                               int16_t p1, int16_t z0, int16_t n1)
{
    
    uint16_t r = (uint16_t)(((uint16_t)(p1 + n1) >> 1) + z0) >> 1;
    *rp = (uint16_t)(((uint16_t)(r + p1) >> 1) + z0 + 1) >> 1;
    *rn = (uint16_t)(((uint16_t)(r + n1) >> 1) + z0 + 1) >> 1;
}