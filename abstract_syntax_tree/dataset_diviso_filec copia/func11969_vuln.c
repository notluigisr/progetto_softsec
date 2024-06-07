static void nalm_dump(FILE * trace, char *data, u32 data_size)
{
	GF_BitStream *bs;

	Bool rle, large_size;
	u32 entry_count;

	if (!data) {
		fprintf(trace, "STR");
		fprintf(trace, "STR");
		fprintf(trace, "STR");
		return;
	}
	
	bs = gf_bs_new(data, data_size, GF_BITSTREAM_READ);
	gf_bs_read_int(bs, 6);
	large_size = gf_bs_read_int(bs, 1);
	rle = gf_bs_read_int(bs, 1);
	entry_count = gf_bs_read_int(bs, large_size ? 16 : 8);
	fprintf(trace, "STR", rle, large_size);
	
	while (entry_count) {
		u32 ID;
		fprintf(trace, "STR");
		if (rle) {
			u32 start_num = gf_bs_read_int(bs, large_size ? 16 : 8);
			fprintf(trace, "STR", start_num);
		}
		ID = gf_bs_read_u16(bs);
		fprintf(trace, "STR", ID);
		entry_count--;
	}
	gf_bs_del(bs);
	fprintf(trace, "STR");
	return;
}