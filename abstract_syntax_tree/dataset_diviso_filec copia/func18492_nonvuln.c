		ds->request_period_switch = new_period_request ? 2 : 1;
		return GF_OK;
	}
	
	return dasher_stream_period_changed(filter, ctx, ds, new_period_request);
}

static void	dasher_check_chaining(GF_DasherCtx *ctx, char *scheme_id, char *url)
{
	GF_MPD_Descriptor *d = gf_mpd_get_descriptor(ctx->mpd->supplemental_properties, scheme_id);
	if (!d && !url) return;
	if (!url) {
		gf_list_del_item(ctx->mpd->supplemental_properties, d);
		gf_mpd_descriptor_free(d);
		return;
	}
	if (d) {
		gf_free(d->value);
		d->value = gf_strdup(url);
		return;