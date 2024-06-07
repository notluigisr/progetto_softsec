GF_Err stbl_box_read(GF_Box *s, GF_BitStream *bs)
{
	GF_Err e;
	
	GF_SampleTableBox *ptr = (GF_SampleTableBox *)s;

	e = gf_isom_box_array_read(s, bs);
	if (e) return e;

	if (!ptr->SyncSample)
		ptr->no_sync_found = 1;

	ptr->nb_sgpd_in_stbl = gf_list_count(ptr->sampleGroupsDescription);
	ptr->nb_stbl_boxes = gf_list_count(ptr->child_boxes);

	if (gf_bs_get_cookie(bs) & GF_ISOM_BS_COOKIE_CLONE_TRACK)
		return GF_OK;



	if (!ptr->_name) {\
		GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("STR", #_name)); \
		return GF_ISOM_INVALID_FILE; \
	}

	CHECK_BOX(SampleToChunk)
	CHECK_BOX(SampleSize)
	CHECK_BOX(ChunkOffset)
	CHECK_BOX(TimeToSample)

	
	if (ptr->SampleSize->sampleCount) {
		if (!ptr->TimeToSample->nb_entries || !ptr->SampleToChunk->nb_entries)
			return GF_ISOM_INVALID_FILE;
	}
	return GF_OK;
}