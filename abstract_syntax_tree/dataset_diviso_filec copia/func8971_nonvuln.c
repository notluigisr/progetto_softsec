void InitSL_RTP(GF_SLConfig *slc)
{
	memset(slc, 0, sizeof(GF_SLConfig));
	slc->tag = GF_ODF_SLC_TAG;
	slc->useTimestampsFlag = 1;
	slc->timestampLength = 32;
}