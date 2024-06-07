RI_FKey_noaction_del(PG_FUNCTION_ARGS)
{
	
	ri_CheckTrigger(fcinfo, "STR", RI_TRIGTYPE_DELETE);

	
	return ri_restrict_del((TriggerData *) fcinfo->context, true);
}