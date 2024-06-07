do_local_notify(xmlNode * notify_src, const char *client_id,
                gboolean sync_reply, gboolean from_peer)
{
    
    cib_client_t *client_obj = NULL;
    int local_rc = pcmk_ok;

    if (client_id != NULL) {
        client_obj = g_hash_table_lookup(client_list, client_id);
    } else {
        crm_trace("STR");
    }

    if (client_obj == NULL) {
        local_rc = -ECONNRESET;

    } else {
        int rid = 0;

        if(sync_reply) {
            CRM_LOG_ASSERT(client_obj->request_id);

            rid = client_obj->request_id;
            client_obj->request_id = 0;

            crm_trace("STR",
                      rid, client_obj->name, from_peer?"STR");

        } else {
            crm_trace("STR",
                      client_obj->name, from_peer?"STR");
        }

        if (client_obj->ipc && crm_ipcs_send(client_obj->ipc, rid, notify_src, !sync_reply) < 0) {
            local_rc = -ENOMSG;

#ifdef HAVE_GNUTLS_GNUTLS_H
        } else if (client_obj->session) {
            crm_send_remote_msg(client_obj->session, notify_src, client_obj->encrypted);
#endif
        } else if(client_obj->ipc == NULL) {
            crm_err("STR", client_obj->name);
        }
    }

    if (local_rc != pcmk_ok && client_obj != NULL) {
        crm_warn("STR",
                 sync_reply ? "STR",
                 client_obj ? client_obj->name : "STR", pcmk_strerror(local_rc));
    }
}