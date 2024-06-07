GF_Err grptype_dump(GF_Box *a, FILE * trace)
{
	u32 i;
	GF_EntityToGroupTypeBox *ptr = (GF_EntityToGroupTypeBox *) a;
	a->type = ptr->grouping_type;
	gf_isom_box_dump_start(a, "STR", trace);
	a->type = GF_ISOM_BOX_TYPE_GRPT;
	fprintf(trace, "STR", ptr->group_id);

	for (i=0; i<ptr->entity_id_count ; i++)
		fprintf(trace, "STR", ptr->entity_ids[i]);

	if (!ptr->size)
		fprintf(trace, "STR");

	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}