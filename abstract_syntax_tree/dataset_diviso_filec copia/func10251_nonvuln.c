ipvs_group_remove_entry(virtual_server_t *vs, virtual_server_group_entry_t *vsge)
{
	real_server_t *rs;
	element e;
	ipvs_service_t srule;
	ipvs_dest_t drule;

	
	ipvs_set_srule(IP_VS_SO_SET_DELDEST, &srule, vs);
	if (vsge->is_fwmark)
		srule.user.fwmark = vsge->vfwmark;
	else
		srule.user.port = inet_sockaddrport(&vsge->addr);

	
	LIST_FOREACH(vs->rs, rs, e) {
		if (rs->alive) {
			
			ipvs_set_drule(IP_VS_SO_SET_DELDEST, &drule, rs);

			
			if (vsge->is_fwmark) {
				
				ipvs_talk(IP_VS_SO_SET_DELDEST, &srule, &drule, NULL, false);
			}
			else
				ipvs_group_range_cmd(IP_VS_SO_SET_DELDEST, &srule, &drule, vsge);
		}
	}

	
	unset_vsge_alive(vsge, vs);
	if (!is_vsge_alive(vsge, vs)) {
		if (vsge->range)
			ipvs_group_range_cmd(IP_VS_SO_SET_DEL, &srule, NULL, vsge);
		else
			ipvs_talk(IP_VS_SO_SET_DEL, &srule, NULL, NULL, false);
	}
}