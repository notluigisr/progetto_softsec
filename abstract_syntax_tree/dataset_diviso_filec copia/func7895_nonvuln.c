GF_Err gf_isom_mvc_config_new(GF_ISOFile *the_file, u32 trackNumber, GF_AVCConfig *cfg, char *URLname, char *URNname, u32 *outDescriptionIndex)
{
	return gf_isom_svc_mvc_config_new(the_file, trackNumber, cfg, GF_TRUE, URLname, URNname,outDescriptionIndex);
}