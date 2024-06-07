static inline int read_bits(
	int bitcount,
	int bitoffset,
	const uint8_t* ptr
) {
	int mask = (1 << bitcount) - 1;
	ptr += bitoffset >> 3;
	bitoffset &= 7;
	int value = ptr[0] | (ptr[1] << 8);
	value >>= bitoffset;
	value &= mask;
	return value;
}