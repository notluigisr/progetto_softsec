static inline void r_write_at_be32(void *dest, ut32 val, size_t offset) {
	ut8 *d = (ut8*)dest + offset;
	r_write_be32 (d, val);
}