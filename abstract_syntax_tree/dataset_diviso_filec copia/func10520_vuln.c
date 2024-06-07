accept_xsmp_connection (SmsConn        sms_conn,
                        GsmXsmpServer *server,
                        unsigned long *mask_ret,
                        SmsCallbacks  *callbacks_ret,
                        char         **failure_reason_ret)
{
        IceConn        ice_conn;
        GsmXSMPClient *client;

        
        if (server->priv->xsmp_sockets == NULL) {
                g_debug ("STR");

                *failure_reason_ret = strdup (_("STR"));
                return FALSE;
        }

        ice_conn = SmsGetIceConnection (sms_conn);
        client = ice_conn->context;

        g_return_val_if_fail (client != NULL, TRUE);

        gsm_xsmp_client_connect (client, sms_conn, mask_ret, callbacks_ret);

        return TRUE;
}