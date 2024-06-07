GF_Err gf_isom_text_reset(GF_TextSample *samp)
{
	if (!samp) return GF_BAD_PARAM;
	if (samp->text) gf_free(samp->text);
	samp->text = NULL;
	samp->len = 0;
	return gf_isom_text_reset_styles(samp);
}