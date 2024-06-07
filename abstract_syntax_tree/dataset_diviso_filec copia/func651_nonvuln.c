static void w2le(uint16_t val, uint16_t *x)
{
	put_unaligned_le16(val, x);
}