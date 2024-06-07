static void gf_dump_vrml_simple_field(GF_SceneDumper *sdump, GF_FieldInfo field, GF_Node *parent)
{
	u32 i, sf_type;
	GF_ChildNodeItem *list;
	void *slot_ptr;

	switch (field.fieldType) {
	case GF_SG_VRML_SFNODE:
		assert ( *(GF_Node **)field.far_ptr);
		gf_dump_vrml_node(sdump, *(GF_Node **)field.far_ptr, 0, NULL);
		return;
	case GF_SG_VRML_MFNODE:
		list = * ((GF_ChildNodeItem **) field.far_ptr);
		assert( list );
		sdump->indent++;
		while (list) {
			gf_dump_vrml_node(sdump, list->node, 1, NULL);
			list = list->next;
		}
		sdump->indent--;
		return;
	case GF_SG_VRML_SFCOMMANDBUFFER:
		return;
	}
	if (gf_sg_vrml_is_sf_field(field.fieldType)) {
		if (sdump->XMLDump) StartAttribute(sdump, "STR");
		gf_dump_vrml_sffield(sdump, field.fieldType, field.far_ptr, 0, parent);
		if (sdump->XMLDump) EndAttribute(sdump);
	} else {
		GenMFField *mffield;
		mffield = (GenMFField *) field.far_ptr;
		sf_type = gf_sg_vrml_get_sf_type(field.fieldType);
		if (!sdump->XMLDump) {
			gf_fprintf(sdump->trace, "STR");
		} else if (sf_type==GF_SG_VRML_SFSTRING) {
			gf_fprintf(sdump->trace, "STR");
		} else {
			StartAttribute(sdump, "STR");
		}
		for (i=0; i<mffield->count; i++) {
			if (i) gf_fprintf(sdump->trace, "STR");
			gf_sg_vrml_mf_get_item(field.far_ptr, field.fieldType, &slot_ptr, i);
			
			gf_dump_vrml_sffield(sdump, sf_type, slot_ptr, 1, parent);
		}
		if (!sdump->XMLDump) {
			gf_fprintf(sdump->trace, "STR");
		} else if (sf_type==GF_SG_VRML_SFSTRING) {
			gf_fprintf(sdump->trace, "STR");
		} else {
			EndAttribute(sdump);
		}
	}
}