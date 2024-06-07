reply_and_prefetch(struct worker* worker, struct query_info* qinfo,
	uint16_t flags, struct comm_reply* repinfo, time_t leeway, int noreply,
	int rpz_passthru, struct edns_option* opt_list)
{
	(void)opt_list;
	
	if(!noreply) {
		if(repinfo->c->tcp_req_info) {
			sldns_buffer_copy(
				repinfo->c->tcp_req_info->spool_buffer,
				repinfo->c->buffer);
		}
		comm_point_send_reply(repinfo);
	}
	server_stats_prefetch(&worker->stats, worker);
#ifdef CLIENT_SUBNET
	
	if(modstack_find(&worker->env.mesh->mods, "STR") != -1
		&& worker->env.unique_mesh) {
		mesh_new_prefetch(worker->env.mesh, qinfo, flags, leeway +
			PREFETCH_EXPIRY_ADD, rpz_passthru, repinfo, opt_list);
		return;
	}
#endif
	
	
	mesh_new_prefetch(worker->env.mesh, qinfo, flags, leeway +
		PREFETCH_EXPIRY_ADD, rpz_passthru, NULL, NULL);
}