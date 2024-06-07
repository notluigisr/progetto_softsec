static void do_client_file_xfer(VirtioPort *vport,
                                VDAgentMessage *message_header,
                                uint8_t *data)
{
    uint32_t msg_type, id;
    UdscsConnection *conn;

    switch (message_header->type) {
    case VD_AGENT_FILE_XFER_START: {
        VDAgentFileXferStartMessage *s = (VDAgentFileXferStartMessage *)data;
        if (!active_session_conn) {
            send_file_xfer_status(vport,
               "STR"
               "STR",
               s->id, VD_AGENT_FILE_XFER_STATUS_VDAGENT_NOT_CONNECTED, NULL, 0);
            return;
        } else if (session_info_session_is_locked(session_info)) {
            syslog(LOG_DEBUG, "STR");
            send_file_xfer_status(vport,
               "STR"
               "STR",
               s->id, VD_AGENT_FILE_XFER_STATUS_SESSION_LOCKED, NULL, 0);
            return;
        }
        msg_type = VDAGENTD_FILE_XFER_START;
        id = s->id;
        
        g_hash_table_insert(active_xfers, GUINT_TO_POINTER(id), active_session_conn);
        break;
    }
    case VD_AGENT_FILE_XFER_STATUS: {
        VDAgentFileXferStatusMessage *s = (VDAgentFileXferStatusMessage *)data;
        msg_type = VDAGENTD_FILE_XFER_STATUS;
        id = s->id;
        break;
    }
    case VD_AGENT_FILE_XFER_DATA: {
        VDAgentFileXferDataMessage *d = (VDAgentFileXferDataMessage *)data;
        msg_type = VDAGENTD_FILE_XFER_DATA;
        id = d->id;
        break;
    }
    default:
        g_return_if_reached(); 
    }

    conn = g_hash_table_lookup(active_xfers, GUINT_TO_POINTER(id));
    if (!conn) {
        if (debug)
            syslog(LOG_DEBUG, "STR", id);
        return;
    }
    udscs_write(conn, msg_type, 0, 0, data, message_header->size);

    
    
    if (message_header->type == VD_AGENT_FILE_XFER_STATUS) {
        g_hash_table_remove(active_xfers, GUINT_TO_POINTER(id));
    }
}