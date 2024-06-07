void fprintUserProp (TNEFStruct *tnef, FILE *fptr, DWORD proptype, DWORD propid, const gchar text[]) {
    variableLength *vl;
    if ((vl=MAPIFindUserProp (&(tnef->MapiProperties), PROP_TAG (proptype, propid))) != MAPI_UNDEFINED) {
        if (vl->size > 0) {
            if ((vl->size == 1) && (vl->data[0] == 0)) {
            } else {
                fprintf (fptr, text, vl->data);
            }
	}
    }
}