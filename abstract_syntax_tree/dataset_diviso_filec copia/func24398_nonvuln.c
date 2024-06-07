			gf_filter_pck_unref(pck);
		}
		ds->nb_sap_in_queue = 0;
	}
	ds->forced_period_switch = GF_FALSE;
}

void dasher_context_update_period_end(GF_DasherCtx *ctx)
{
	u32 i, count;

	if (!ctx->mpd) return;

	count = gf_list_count(ctx->current_period->streams);
	for (i=0; i<count; i++) {
		GF_DashStream *ds = gf_list_get(ctx->current_period->streams, i);
		if (!ds->rep) continue;
		if (!ds->rep->dasher_ctx) continue;
		if (ds->done == 1) {
			ds->rep->dasher_ctx->done = 1;
		} else {
			
			ds->rep->dasher_ctx->last_pck_idx = ds->nb_pck;
			ds->seek_to_pck = ds->nb_pck;
			ds->rep->dasher_ctx->seg_number = ds->seg_number;
			ds->rep->dasher_ctx->next_seg_start = ds->next_seg_start;
			ds->rep->dasher_ctx->first_cts = ds->first_cts;
			ds->rep->dasher_ctx->first_dts = ds->first_dts;
			ds->rep->dasher_ctx->ts_offset = ds->ts_offset;
			ds->rep->dasher_ctx->segs_purged = ds->nb_segments_purged;
			ds->rep->dasher_ctx->dur_purged = ds->dur_purged;
			ds->rep->dasher_ctx->moof_sn = ds->moof_sn;
			ds->rep->dasher_ctx->moof_sn_inc = ds->moof_sn_inc;
			ds->rep->dasher_ctx->subdur_forced = ds->subdur_forced_use_period_dur ? GF_TRUE : GF_FALSE;
		}
		if (ctx->subdur) {
			ds->rep->dasher_ctx->cumulated_subdur = ds->cumulated_subdur + ctx->subdur;
			ds->rep->dasher_ctx->cumulated_dur = ((Double)ds->cumulated_dur) / ds->timescale;

		}
		ds->rep->dasher_ctx->nb_repeat = ds->nb_repeat;
		ds->rep->dasher_ctx->est_next_dts = ds->est_next_dts;
		ds->rep->dasher_ctx->source_pid = ds->id;
		ds->rep->dasher_ctx->mpd_timescale = ds->mpd_timescale;