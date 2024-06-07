static void gf_dump_vrml_proto_field(GF_SceneDumper *sdump, GF_Node *node, GF_FieldInfo field)
{
	u32 i, sf_type;
	void *slot_ptr;

	DUMP_IND(sdump);
	gf_fprintf(sdump->trace, "STR", field.name);
	if (gf_sg_vrml_is_sf_field(field.fieldType)) {
		if (field.fieldType == GF_SG_VRML_SFNODE) {
			gf_fprintf(sdump->trace, "STR");
			sdump->indent++;
			if (!sdump->X3DDump) gf_fprintf(sdump->trace, "STR");
			gf_dump_vrml_node(sdump, field.far_ptr ? *(GF_Node **)field.far_ptr : NULL, 0, NULL);
			if (!sdump->X3DDump) gf_fprintf(sdump->trace, "STR");
			sdump->indent--;
			DUMP_IND(sdump);
			gf_fprintf(sdump->trace, "STR");
		} else {
			if (sdump->X3DDump) {
				gf_fprintf(sdump->trace, "STR");
			} else {
				gf_fprintf(sdump->trace, "STR", GetXMTFieldTypeValueName(field.fieldType));
			}
			gf_dump_vrml_sffield(sdump, field.fieldType, field.far_ptr, 0, node);
			gf_fprintf(sdump->trace, "STR");
		}
	} else {
		GenMFField *mffield = (GenMFField *) field.far_ptr;
		sf_type = gf_sg_vrml_get_sf_type(field.fieldType);

		if ((field.eventType==GF_SG_EVENT_FIELD) || (field.eventType==GF_SG_EVENT_EXPOSED_FIELD)) {
			if (sf_type == GF_SG_VRML_SFNODE) {
				GF_ChildNodeItem *list = *(GF_ChildNodeItem **)field.far_ptr;
				gf_fprintf(sdump->trace, "STR");
				sdump->indent++;
				if (!sdump->X3DDump) gf_fprintf(sdump->trace, "STR");
				while (list) {
					gf_dump_vrml_node(sdump, list->node, 1, NULL);
					list = list->next;
				}
				if (!sdump->X3DDump) gf_fprintf(sdump->trace, "STR");
				sdump->indent--;
				DUMP_IND(sdump);
				gf_fprintf(sdump->trace, "STR");
			} else {
				if (sdump->X3DDump) {
					gf_fprintf(sdump->trace, "STR");
				} else {
					gf_fprintf(sdump->trace, "STR", GetXMTFieldTypeValueName(field.fieldType));
				}
				if (mffield) {
					for (i=0; i<mffield->count; i++) {
						if (i) gf_fprintf(sdump->trace, "STR");
						if (field.fieldType != GF_SG_VRML_MFNODE) {
							gf_sg_vrml_mf_get_item(field.far_ptr, field.fieldType, &slot_ptr, i);
							gf_dump_vrml_sffield(sdump, sf_type, slot_ptr, (mffield->count>1) ? 1 : 0, node);
						}
					}
				}
				gf_fprintf(sdump->trace, "STR");
			}
		}
	}
}