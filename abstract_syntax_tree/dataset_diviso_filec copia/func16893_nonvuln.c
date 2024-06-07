		GF_DashStream *ds = gf_list_get(ctx->pids, i);
		if (pid_id && (ds->pid_id==pid_id)) return ds;
		if (src_url && ds->src_url && !strcmp(ds->src_url, src_url) && (ds->id == original_pid) ) return ds;
	}
	return NULL;
}

static GF_Err dasher_reload_muxed_comp(GF_DasherCtx *ctx, GF_DashStream *base_ds, char *mux_pids, Bool check_only)
{
	GF_Err e = GF_OK;
	while (mux_pids) {
		u32 pid_id;
		GF_DashStream *ds;
		char *sep = strchr(mux_pids, ' ');
		if (sep) sep[0] = 0;

		pid_id = atoi(mux_pids);
		ds = dasher_get_stream(ctx, base_ds->src_url, pid_id, 0);
		if (ds) {
			if (!check_only) {
				if (ds->rep) gf_mpd_representation_free(ds->rep);
				ds->rep = NULL;
				ds->set = base_ds->set;
				ds->muxed_base = base_ds;
				base_ds->nb_comp ++;
				ds->nb_comp = 1;
				ds->done = base_ds->done;
				ds->subdur_done = base_ds->subdur_done;
				ds->period = ctx->current_period;

				gf_list_del_item(ctx->next_period->streams, ds);
				gf_list_add(ctx->current_period->streams, ds);
			}
		} else {
			GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("STR", pid_id, base_ds->src_url));
			e = GF_BAD_PARAM;
		}

		if (!sep) break;