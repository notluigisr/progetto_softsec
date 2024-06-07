static inline void glue(rop_32_,ROP_NAME)(uint32_t *dst, uint32_t src)
{
    *dst = ROP_FN(*dst, src);
}