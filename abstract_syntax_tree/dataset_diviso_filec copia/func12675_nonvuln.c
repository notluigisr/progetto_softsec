GF_Err odtt_box_dump(GF_Box *a, FILE * trace)
{
	GF_OMADRMTransactionTrackingBox *ptr = (GF_OMADRMTransactionTrackingBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);

	gf_fprintf(trace, "STR");
	dump_data(trace, ptr->TransactionID, 16);
	gf_fprintf(trace, "STR");
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}