GF_Box *dvvC_box_new()
{
	GF_DOVIConfigurationBox *tmp = (GF_DOVIConfigurationBox *)gf_malloc(sizeof(GF_DOVIConfigurationBox));
	if (tmp == NULL) return NULL;
	memset(tmp, 0, sizeof(GF_DOVIConfigurationBox));
	tmp->type = GF_ISOM_BOX_TYPE_DVVC;
	return (GF_Box *)tmp;
}