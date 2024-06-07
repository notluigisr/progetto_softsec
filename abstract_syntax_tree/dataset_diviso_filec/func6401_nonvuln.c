disconnect_remote_client(gpointer key, gpointer value, gpointer user_data)
{
    cib_client_t *a_client = value;
    crm_err("STR", crm_str(a_client->name));
}