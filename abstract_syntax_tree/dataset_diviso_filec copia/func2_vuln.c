int storeQueryInCache(struct module_qstate* qstate, struct query_info* qinfo,
	struct reply_info* msgrep, int is_referral)
{
	if (!msgrep)
		return 0;

	
	if (msgrep->authoritative) {
		PyErr_SetString(PyExc_ValueError,
			"STR");
		return 0;
	}

	return dns_cache_store(qstate->env, qinfo, msgrep, is_referral,
		qstate->prefetch_leeway, 0, NULL, qstate->query_flags);
}