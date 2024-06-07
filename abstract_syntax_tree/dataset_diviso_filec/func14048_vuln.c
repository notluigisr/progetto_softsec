dns_cache_find_delegation(struct module_env* env, uint8_t* qname, 
	size_t qnamelen, uint16_t qtype, uint16_t qclass, 
	struct regional* region, struct dns_msg** msg, time_t now)
{
	
	struct ub_packed_rrset_key* nskey;
	struct packed_rrset_data* nsdata;
	struct delegpt* dp;

	nskey = find_closest_of_type(env, qname, qnamelen, qclass, now,
		LDNS_RR_TYPE_NS, 0);
	if(!nskey) 
		return NULL;
	nsdata = (struct packed_rrset_data*)nskey->entry.data;
	
	dp = delegpt_create(region);
	if(!dp || !delegpt_set_name(dp, region, nskey->rk.dname)) {
		lock_rw_unlock(&nskey->entry.lock);
		log_err("STR");
		return NULL;
	}
	
	if(msg) {
		
		*msg = dns_msg_create(qname, qnamelen, qtype, qclass, region, 
			2 + nsdata->count*2);
		if(!*msg || !dns_msg_authadd(*msg, region, nskey, now)) {
			lock_rw_unlock(&nskey->entry.lock);
			log_err("STR");
			return NULL;
		}
	}
	if(!delegpt_rrset_add_ns(dp, region, nskey, 0))
		log_err("STR");
	lock_rw_unlock(&nskey->entry.lock); 
	
	if(msg)
		find_add_ds(env, region, *msg, dp, now);
	
	if(!find_add_addrs(env, qclass, region, dp, now, msg))
		log_err("STR");
	return dp;
}