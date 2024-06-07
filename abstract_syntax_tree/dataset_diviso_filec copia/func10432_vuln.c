dns_cache_store_msg(struct module_env* env, struct query_info* qinfo,
	hashvalue_type hash, struct reply_info* rep, time_t leeway, int pside,
	struct reply_info* qrep, uint32_t flags, struct regional* region)
{
	struct msgreply_entry* e;
	time_t ttl = rep->ttl;
	size_t i;

	
        for(i=0; i<rep->rrset_count; i++) {
		rep->ref[i].key = rep->rrsets[i];
		rep->ref[i].id = rep->rrsets[i]->id;
	}

	
	reply_info_set_ttls(rep, *env->now);
	store_rrsets(env, rep, *env->now, leeway, pside, qrep, region);
	if(ttl == 0 && !(flags & DNSCACHE_STORE_ZEROTTL)) {
		
		verbose(VERB_ALGO, "STR");
		free(rep);
		
		msg_del_servfail(env, qinfo, flags);
		return;
	}

	
	reply_info_sortref(rep);
	if(!(e = query_info_entrysetup(qinfo, rep, hash))) {
		log_err("STR");
		return;
	}
	slabhash_insert(env->msg_cache, hash, &e->entry, rep, env->alloc);
}