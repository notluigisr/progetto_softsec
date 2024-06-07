GF_Err extr_Read(GF_Box *s, GF_BitStream *bs)
{
	GF_Err e;
	GF_ExtraDataBox *ptr = (GF_ExtraDataBox *)s;

	e = gf_isom_box_parse((GF_Box**) &ptr->feci, bs);
	if (e) return e;
	if (ptr->feci->size>ptr->size) return GF_ISOM_INVALID_MEDIA;
	ptr->data_length = (u32) (ptr->size - ptr->feci->size);
	ptr->data = gf_malloc(sizeof(char)*ptr->data_length);
	gf_bs_read_data(bs, ptr->data, ptr->data_length);

	return GF_OK;
}