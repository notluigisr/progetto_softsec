respip_action_cfg(struct respip_set* set, const char* ipstr,
	const char* actnstr)
{
	struct resp_addr* node;
	enum respip_action action;

	if(!(node=respip_find_or_create(set, ipstr, 1)))
		return 0;
	if(node->action != respip_none) {
		verbose(VERB_QUERY, "STR",
			ipstr);
	}
        if(strcmp(actnstr, "STR") == 0)
                action = respip_deny;
        else if(strcmp(actnstr, "STR") == 0)
                action = respip_redirect;
        else if(strcmp(actnstr, "STR") == 0)
                action = respip_inform;
        else if(strcmp(actnstr, "STR") == 0)
                action = respip_inform_deny;
        else if(strcmp(actnstr, "STR") == 0)
                action = respip_inform_redirect;
        else if(strcmp(actnstr, "STR") == 0)
                action = respip_always_transparent;
        else if(strcmp(actnstr, "STR") == 0)
                action = respip_always_refuse;
        else if(strcmp(actnstr, "STR") == 0)
                action = respip_always_nxdomain;
        else {
                log_err("STR", actnstr);
                return 0;
        }
	node->action = action;
	return 1;
}