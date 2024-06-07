static GF_Err gf_sm_setup_lsrenc(GF_SceneEngine *seng, GF_StreamContext *sc, GF_ESD *esd)
{
	u8 *data;
	u32 data_len;
	GF_LASERConfig lsr_cfg;

	if (!esd->decoderConfig || (esd->decoderConfig->streamType != GF_STREAM_SCENE)) return GF_BAD_PARAM;

	seng->lsrenc = gf_laser_encoder_new(seng->ctx->scene_graph);

	
	if (!esd->decoderConfig->decoderSpecificInfo) {
		memset(&lsr_cfg, 0, sizeof(GF_LASERConfig));
	}
	
	else if (esd->decoderConfig->decoderSpecificInfo->tag == GF_ODF_LASER_CFG_TAG) {
		memcpy(&lsr_cfg, (GF_LASERConfig *)esd->decoderConfig->decoderSpecificInfo, sizeof(GF_LASERConfig) );
	}
	
	else {
		gf_odf_get_laser_config(esd->decoderConfig->decoderSpecificInfo, &lsr_cfg);
	}

	gf_laser_encoder_new_stream(seng->lsrenc, esd->ESID , &lsr_cfg);

	gf_laser_encoder_get_config(seng->lsrenc, esd->ESID, &data, &data_len);

	if (esd->decoderConfig->decoderSpecificInfo) gf_odf_desc_del((GF_Descriptor *) esd->decoderConfig->decoderSpecificInfo);
	esd->decoderConfig->decoderSpecificInfo = (GF_DefaultDescriptor *) gf_odf_desc_new(GF_ODF_DSI_TAG);
	esd->decoderConfig->decoderSpecificInfo->data = data;
	esd->decoderConfig->decoderSpecificInfo->dataLength = data_len;

	sc->dec_cfg = (char*)gf_malloc(sizeof(char)*data_len);
	memcpy(sc->dec_cfg, data, data_len);
	sc->dec_cfg_len = data_len;
	return GF_OK;
}