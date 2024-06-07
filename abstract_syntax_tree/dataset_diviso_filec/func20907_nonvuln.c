PJ_DEF(pjsua_msg_data*) pjsua_msg_data_clone(pj_pool_t *pool,
                                             const pjsua_msg_data *rhs)
{
    pjsua_msg_data *msg_data;
    const pjsip_hdr *hdr;
    const pjsip_multipart_part *mpart;

    PJ_ASSERT_RETURN(pool && rhs, NULL);

    msg_data = PJ_POOL_ZALLOC_T(pool, pjsua_msg_data);
    PJ_ASSERT_RETURN(msg_data != NULL, NULL);

    pj_strdup(pool, &msg_data->target_uri, &rhs->target_uri);

    pj_list_init(&msg_data->hdr_list);
    hdr = rhs->hdr_list.next;
    while (hdr != &rhs->hdr_list) {
	pj_list_push_back(&msg_data->hdr_list, pjsip_hdr_clone(pool, hdr));
	hdr = hdr->next;
    }

    pj_strdup(pool, &msg_data->content_type, &rhs->content_type);
    pj_strdup(pool, &msg_data->msg_body, &rhs->msg_body);

    pjsip_media_type_cp(pool, &msg_data->multipart_ctype,
                        &rhs->multipart_ctype);

    pj_list_init(&msg_data->multipart_parts);
    mpart = rhs->multipart_parts.next;
    while (mpart != &rhs->multipart_parts) {
	pj_list_push_back(&msg_data->multipart_parts,
                          pjsip_multipart_clone_part(pool, mpart));
	mpart = mpart->next;
    }

    return msg_data;
}