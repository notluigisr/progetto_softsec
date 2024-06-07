PJ_DEF(pj_status_t) pjsip_tpmgr_find_local_addr( pjsip_tpmgr *tpmgr,
						 pj_pool_t *pool,
						 pjsip_transport_type_e type,
						 const pjsip_tpselector *sel,
						 pj_str_t *ip_addr,
						 int *port)
{
    pjsip_tpmgr_fla2_param prm;
    pj_status_t status;

    pjsip_tpmgr_fla2_param_default(&prm);
    prm.tp_type = type;
    prm.tp_sel = sel;

    status = pjsip_tpmgr_find_local_addr2(tpmgr, pool, &prm);
    if (status != PJ_SUCCESS)
	return status;

    *ip_addr = prm.ret_addr;
    *port = prm.ret_port;

    return PJ_SUCCESS;
}