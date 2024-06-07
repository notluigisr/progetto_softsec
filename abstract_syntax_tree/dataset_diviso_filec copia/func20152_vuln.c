static inline void glue(rop_16_,ROP_NAME)(uint16_t *dst, uint16_t src)
{
    *dst = ROP_FN(*dst, src);
}