GF_Err gf_isom_flac_config_get(GF_ISOFile *the_file, u32 trackNumber, u32 StreamDescriptionIndex, u8 **dsi, u32 *dsi_size)
{
	u32 type;
	GF_TrackBox *trak;
	GF_MPEGAudioSampleEntryBox *entry;
	trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (dsi) *dsi = NULL;
	if (dsi_size) *dsi_size = 0;
	if (!trak || !StreamDescriptionIndex) return GF_BAD_PARAM;

	entry = (GF_MPEGAudioSampleEntryBox *)gf_list_get(trak->Media->information->sampleTable->SampleDescription->child_boxes, StreamDescriptionIndex-1);

	type = entry->type;
	if (type==GF_ISOM_BOX_TYPE_ENCA) {
		gf_isom_get_original_format_type(the_file, trackNumber, StreamDescriptionIndex, &type);
	}

	if (type!=GF_ISOM_BOX_TYPE_FLAC) return GF_BAD_PARAM;
	if (!entry->cfg_flac) return GF_OK;
	if (dsi) {
		*dsi = gf_malloc(sizeof(u8)*entry->cfg_flac->dataSize);
		memcpy(*dsi, entry->cfg_flac->data, entry->cfg_flac->dataSize);
	}
	if (dsi_size) *dsi_size = entry->cfg_flac->dataSize;
	return GF_OK;
}