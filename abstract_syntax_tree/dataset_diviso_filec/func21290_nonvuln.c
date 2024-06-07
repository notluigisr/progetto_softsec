void cil_destroy_classpermission(struct cil_classpermission *cp)
{
	if (cp == NULL) {
		return;
	}

	if (cp->datum.name != NULL) {
		cil_list_destroy(&cp->classperms, CIL_FALSE);
	} else {
		
		cil_destroy_classperms_list(&cp->classperms);
	}

	cil_symtab_datum_destroy(&cp->datum);


	free(cp);
}