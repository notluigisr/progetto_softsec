void fprintProperty (TNEFStruct *tnef, FILE *fptr, DWORD proptype, DWORD propid, const gchar text[]) {
    variableLength *vl;
    if ((vl=MAPIFindProperty (&(tnef->MapiProperties), PROP_TAG (proptype, propid))) != MAPI_UNDEFINED) {
        if (vl->size > 0) {
            if ((vl->size == 1) && (vl->data[0] == 0)) {
            } else {
                fprintf (fptr, text, vl->data);
            }
	}
    }
}