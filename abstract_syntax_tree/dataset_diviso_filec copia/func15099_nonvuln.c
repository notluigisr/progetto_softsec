GF_Box *gen_sample_entry_New()
{
	ISOM_DECL_BOX_ALLOC(GF_SampleEntryBox, GF_QT_BOX_TYPE_C608);
	gf_isom_sample_entry_init((GF_SampleEntryBox*)tmp);
	return (GF_Box *)tmp;
}