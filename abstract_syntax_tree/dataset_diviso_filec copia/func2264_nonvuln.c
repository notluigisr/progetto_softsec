static u32 dasher_get_dep_bitrate(GF_DasherCtx *ctx, GF_DashStream *ds)
{
	u32 bitrate = ds->bitrate;
	if (ds->dep_id) {
		u32 i, count = gf_list_count(ctx->current_period->streams);
		for (i=0; i<count; i++) {
			GF_DashStream *a_ds = gf_list_get(ctx->current_period->streams, i);
			if (a_ds == ds) continue;

			if (gf_list_find(a_ds->complementary_streams, ds)>=0) {

				bitrate += dasher_get_dep_bitrate(ctx, a_ds);
			}
		}
	}
	return bitrate;
}