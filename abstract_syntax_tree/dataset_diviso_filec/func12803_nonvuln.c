ThrowErrorData(ErrorData *edata)
{
	ErrorData *newedata;
	MemoryContext	oldcontext;

	if (!errstart(edata->elevel, edata->filename, edata->lineno,
				  edata->funcname, NULL))
		return;

	newedata = &errordata[errordata_stack_depth];
	oldcontext = MemoryContextSwitchTo(edata->assoc_context);

	
	if (edata->sqlerrcode > 0)
		newedata->sqlerrcode = edata->sqlerrcode;
	if (edata->message)
		newedata->message = pstrdup(edata->message);
	if (edata->detail)
		newedata->detail = pstrdup(edata->detail);
	if (edata->detail_log)
		newedata->detail_log = pstrdup(edata->detail_log);
	if (edata->hint)
		newedata->hint = pstrdup(edata->hint);
	if (edata->context)
		newedata->context = pstrdup(edata->context);
	if (edata->schema_name)
		newedata->schema_name = pstrdup(edata->schema_name);
	if (edata->table_name)
		newedata->table_name = pstrdup(edata->table_name);
	if (edata->column_name)
		newedata->column_name = pstrdup(edata->column_name);
	if (edata->datatype_name)
		newedata->datatype_name = pstrdup(edata->datatype_name);
	if (edata->constraint_name)
		newedata->constraint_name = pstrdup(edata->constraint_name);
	if (edata->internalquery)
		newedata->internalquery = pstrdup(edata->internalquery);

	MemoryContextSwitchTo(oldcontext);

	errfinish(0);
}