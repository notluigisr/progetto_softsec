
		return rfc6381_codec_name_default(szCodec, subtype, ds->codec_id);
	}
	return GF_OK;
}


static GF_DashStream *get_base_ds(GF_DasherCtx *ctx, GF_DashStream *for_ds)
{
	u32 i, count;
	if (!for_ds->dep_id) return NULL;
	count = gf_list_count(ctx->pids);