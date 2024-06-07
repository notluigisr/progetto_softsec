fmgr_info(Oid functionId, FmgrInfo *finfo)
{
	fmgr_info_cxt_security(functionId, finfo, CurrentMemoryContext, false);
}