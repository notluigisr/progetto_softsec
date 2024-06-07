_sv_to_datum_finfo(Oid typid, FmgrInfo *finfo, Oid *typioparam)
{
	Oid			typinput;

	
	getTypeInputInfo(typid,
					 &typinput, typioparam);
	fmgr_info(typinput, finfo);
}