PJ_DEF(pj_status_t) pjsip_auth_clt_clone( pj_pool_t *pool,
					  pjsip_auth_clt_sess *sess,
					  const pjsip_auth_clt_sess *rhs )
{
    unsigned i;

    PJ_ASSERT_RETURN(pool && sess && rhs, PJ_EINVAL);

    pjsip_auth_clt_init(sess, (pjsip_endpoint*)rhs->endpt, pool, 0);

    sess->cred_cnt = rhs->cred_cnt;
    sess->cred_info = (pjsip_cred_info*)
    		      pj_pool_alloc(pool,
				    sess->cred_cnt*sizeof(pjsip_cred_info));
    for (i=0; i<rhs->cred_cnt; ++i) {
	pj_strdup(pool, &sess->cred_info[i].realm, &rhs->cred_info[i].realm);
	pj_strdup(pool, &sess->cred_info[i].scheme, &rhs->cred_info[i].scheme);
	pj_strdup(pool, &sess->cred_info[i].username,
		  &rhs->cred_info[i].username);
	sess->cred_info[i].data_type = rhs->cred_info[i].data_type;
	pj_strdup(pool, &sess->cred_info[i].data, &rhs->cred_info[i].data);
    }

    
    PJ_TODO(FULL_CLONE_OF_AUTH_CLIENT_SESSION);

    return PJ_SUCCESS;
}