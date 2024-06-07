static void dasher_send_encode_hints(GF_DasherCtx *ctx, GF_DashStream *ds)
{
	if (!ctx->sfile && !ds->stl && !ctx->use_cues) {
		GF_FilterEvent evt;
		GF_FEVT_INIT(evt, GF_FEVT_ENCODE_HINTS, ds->ipid)
		evt.encode_hints.intra_period = ds->dash_dur;
		gf_filter_pid_send_event(ds->ipid, &evt);
	}
}