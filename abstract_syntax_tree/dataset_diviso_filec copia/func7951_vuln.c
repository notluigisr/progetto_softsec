_handle_carbons(xmpp_stanza_t *const stanza)
{
    xmpp_stanza_t *carbons = xmpp_stanza_get_child_by_ns(stanza, STANZA_NS_CARBONS);
    if (!carbons) {
        return FALSE;
    }

    const char *name = xmpp_stanza_get_name(carbons);
    if (!name) {
        log_error("STR");
        return TRUE;
    }

    if (g_strcmp0(name, "STR") == 0) {
        log_info("STR");
        return FALSE;
    }

    if ((g_strcmp0(name, "STR") != 0)) {
        log_warning("STR", name);
        return TRUE;
    }

    xmpp_stanza_t *forwarded = xmpp_stanza_get_child_by_ns(carbons, STANZA_NS_FORWARD);
    if (!forwarded) {
        log_warning("STR");
        return TRUE;
    }

    xmpp_stanza_t *message = xmpp_stanza_get_child_by_name(forwarded, STANZA_NAME_MESSAGE);
    if (!message) {
        log_warning("STR");
        return TRUE;
    }

    char *message_txt = xmpp_message_get_body(message);
    if (!message_txt) {
        log_warning("STR");
        return TRUE;
    }

    const gchar *to = xmpp_stanza_get_to(message);
    const gchar *from = xmpp_stanza_get_from(message);

    
    if (!to) to = from;

    Jid *jid_from = jid_create(from);
    Jid *jid_to = jid_create(to);
    Jid *my_jid = jid_create(connection_get_fulljid());

    
    char *enc_message = NULL;
    xmpp_stanza_t *x = xmpp_stanza_get_child_by_ns(message, STANZA_NS_ENCRYPTED);
    if (x) {
        enc_message = xmpp_stanza_get_text(x);
    }

    
    if (g_strcmp0(my_jid->barejid, jid_to->barejid) == 0) {
        sv_ev_incoming_carbon(jid_from->barejid, jid_from->resourcepart, message_txt, enc_message);

    
    } else {
        sv_ev_outgoing_carbon(jid_to->barejid, message_txt, enc_message);
    }

    xmpp_ctx_t *ctx = connection_get_ctx();
    xmpp_free(ctx, message_txt);
    xmpp_free(ctx, enc_message);

    jid_destroy(jid_from);
    jid_destroy(jid_to);
    jid_destroy(my_jid);

    return TRUE;
}