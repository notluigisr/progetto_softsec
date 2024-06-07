void jp2_box_dump(jp2_box_t *box, FILE *out)
{
	jp2_boxinfo_t *boxinfo;
	boxinfo = jp2_boxinfolookup(box->type);
	assert(boxinfo);

	fprintf(out, "STR");
	fprintf(out, "STR"', boxinfo->name,
	  '"', box->type, box->len);
	if (box->ops->dumpdata) {
		(*box->ops->dumpdata)(box, out);
	}
}