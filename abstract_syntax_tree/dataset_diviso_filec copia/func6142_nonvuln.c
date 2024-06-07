}
static void amix_set_s32(u8 *data, Double val)
{
	val *= 0xFFFFFFFF;
	u32 res = (u32) val;
	data[0] = res & 0xFF;
	data[1] = (res>>8) & 0xFF;
	data[2] = (res>>16) & 0xFF;
	data[3] = (res>>24) & 0xFF;