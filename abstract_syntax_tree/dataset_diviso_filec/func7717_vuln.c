static inline void glue(rop_8_,ROP_NAME)(uint8_t *dst, uint8_t src)
{
    *dst = ROP_FN(*dst, src);
}