static pj_status_t restart_listener(pjsua_transport_id id,
				    unsigned restart_lis_delay)
{
    pj_sockaddr bind_addr;
    pjsua_transport_info tp_info;
    pj_status_t status;

    pjsua_transport_get_info(id, &tp_info);
    pj_sockaddr_init(pjsip_transport_type_get_af(tp_info.type),
		     &bind_addr,
		     NULL,
		     pj_sockaddr_get_port(&tp_info.local_addr));

    switch (tp_info.type) {
    case PJSIP_TRANSPORT_UDP:
    case PJSIP_TRANSPORT_UDP6:    
    {
	unsigned num_locks = 0;

	
	while (PJSUA_LOCK_IS_LOCKED()) {
    	    num_locks++;
    	    PJSUA_UNLOCK();
	}

	status = pjsip_udp_transport_restart2(
				       pjsua_var.tpdata[id].data.tp,
				       PJSIP_UDP_TRANSPORT_DESTROY_SOCKET,
				       PJ_INVALID_SOCKET,
				       &bind_addr,
				       NULL);

	
	for (;num_locks > 0; num_locks--)
    	    PJSUA_LOCK();

    }
	break;

#if defined(PJSIP_HAS_TLS_TRANSPORT) && PJSIP_HAS_TLS_TRANSPORT!=0
    case PJSIP_TRANSPORT_TLS:
    case PJSIP_TRANSPORT_TLS6:
	status = pjsip_tls_transport_restart(
					pjsua_var.tpdata[id].data.factory,
					&bind_addr,
					NULL);
	break;
#endif
    case PJSIP_TRANSPORT_TCP:
    case PJSIP_TRANSPORT_TCP6:
	status = pjsip_tcp_transport_restart(
					pjsua_var.tpdata[id].data.factory,
					&bind_addr,
					NULL);
	break;

    default:
	status = PJ_EINVAL;
    }

    PJ_PERROR(3,(THIS_FILE, status, "STR",
		 tp_info.info.slen, tp_info.info.ptr));

    if (status != PJ_SUCCESS && (restart_lis_delay > 0)) {
	
	pjsua_schedule_timer2(&restart_listener_cb,
			      (void*)(pj_size_t)id,
			      restart_lis_delay);

	PJ_LOG(3,(THIS_FILE, "STR",
		  tp_info.info.slen, tp_info.info.ptr, restart_lis_delay));

	status = PJ_SUCCESS;
    } else {
	int i = 0;
	pj_bool_t all_done = PJ_TRUE;

	pjsua_var.tpdata[id].is_restarting = PJ_FALSE;
	pjsua_var.tpdata[id].restart_status = status;
	if (pjsua_var.ua_cfg.cb.on_ip_change_progress) {
	    pjsua_ip_change_op_info info;

	    pj_bzero(&info, sizeof(info));
	    info.lis_restart.transport_id = id;
	    pjsua_var.ua_cfg.cb.on_ip_change_progress(
						PJSUA_IP_CHANGE_OP_RESTART_LIS,
						status,
						&info);
	}

	
	for (; i < PJ_ARRAY_SIZE(pjsua_var.tpdata); ++i) {
	    if (pjsua_var.tpdata[i].data.ptr != NULL &&
		pjsua_var.tpdata[i].is_restarting)
	    {
		all_done = PJ_FALSE;
		break;
	    }
	}
	if (all_done)
	    status = handle_ip_change_on_acc();
    }
    return status;
}