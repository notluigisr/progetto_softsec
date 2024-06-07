static int types_equal(const struct cli_bc *bc, uint16_t *apity2ty, uint16_t tid, uint16_t apitid)
{
    unsigned i;
    const struct cli_bc_type *ty = &bc->types[tid - 65];
    const struct cli_bc_type *apity = &cli_apicall_types[apitid];
    
     if (apity2ty[apitid] == tid + 1)
	return 1;
     apity2ty[apitid] = tid+1;

     if (ty->kind != apity->kind) {
	 cli_dbgmsg("STR", ty->kind, apity->kind);
	 return 0;
     }
     if (ty->numElements != apity->numElements) {
	 cli_dbgmsg("STR", ty->numElements, apity->numElements);
	 return 0;
     }
     for (i=0;i<ty->numElements;i++) {
	if (apity->containedTypes[i] < BC_START_TID) {
	    if (ty->containedTypes[i] != apity->containedTypes[i]) {
		cli_dbgmsg("STR",
			   ty->containedTypes[i], apity->containedTypes[i]);
		return 0;
	    }
	} else if (!types_equal(bc, apity2ty, ty->containedTypes[i], apity->containedTypes[i] - BC_START_TID))
	    return 0;
	if (ty->kind == DArrayType)
	    break;
     }
    return 1;
}