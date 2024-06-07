GF_Err gf_isom_set_extraction_slc(GF_ISOFile *the_file, u32 trackNumber, u32 StreamDescriptionIndex, const GF_SLConfig *slConfig)
{
	GF_TrackBox *trak;
	GF_SampleEntryBox *entry;
	GF_Err e;
	GF_SLConfig **slc;
	GF_ESDBox *esds;

	trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (!trak) return GF_BAD_PARAM;

	e = Media_GetSampleDesc(trak->Media, StreamDescriptionIndex, &entry, NULL);
	if (e) return e;

	
	switch (entry->type) {
	case GF_ISOM_BOX_TYPE_MP4S:
		esds = ((GF_MPEGSampleEntryBox *)entry)->esd;
		if (!esds || !esds->desc || !esds->desc->slConfig || (esds->desc->slConfig->predefined != SLPredef_MP4))
			return GF_ISOM_INVALID_FILE;
		slc = & ((GF_MPEGSampleEntryBox *)entry)->slc;
		break;
	case GF_ISOM_BOX_TYPE_MP4A:
		esds = ((GF_MPEGAudioSampleEntryBox *)entry)->esd;
		if (!esds || !esds->desc || !esds->desc->slConfig || (esds->desc->slConfig->predefined != SLPredef_MP4))
			return GF_ISOM_INVALID_FILE;
		slc = & ((GF_MPEGAudioSampleEntryBox *)entry)->slc;
		break;
	case GF_ISOM_BOX_TYPE_MP4V:
		esds = ((GF_MPEGVisualSampleEntryBox *)entry)->esd;
		if (!esds || !esds->desc || !esds->desc->slConfig || (esds->desc->slConfig->predefined != SLPredef_MP4))
			return GF_ISOM_INVALID_FILE;
		slc = & ((GF_MPEGVisualSampleEntryBox *)entry)->slc;
		break;
	default:
		return GF_BAD_PARAM;
	}

	if (*slc) {
		gf_odf_desc_del((GF_Descriptor *)*slc);
		*slc = NULL;
	}
	if (!slConfig) return GF_OK;
	
	return gf_odf_desc_copy((GF_Descriptor *) slConfig, (GF_Descriptor **) slc);
}