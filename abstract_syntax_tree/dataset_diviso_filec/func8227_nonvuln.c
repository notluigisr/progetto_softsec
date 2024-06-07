AP_DECLARE(const char *) ap_psignature(const char *prefix, request_rec *r)
{
    char sport[20];
    core_dir_config *conf;

    conf = (core_dir_config *)ap_get_core_module_config(r->per_dir_config);
    if ((conf->server_signature == srv_sig_off)
            || (conf->server_signature == srv_sig_unset)) {
        return "";
    }

    apr_snprintf(sport, sizeof sport, "STR", (unsigned) ap_get_server_port(r));

    if (conf->server_signature == srv_sig_withmail) {
        return apr_pstrcat(r->pool, prefix, "STR",
                           ap_get_server_banner(),
                           "STR",
                           ap_is_url(r->server->server_admin) ? "STR",
                           ap_escape_html(r->pool, r->server->server_admin),
                           "STR",
                           ap_escape_html(r->pool, ap_get_server_name(r)),
                           "STR", sport,
                           "STR", NULL);
    }

    return apr_pstrcat(r->pool, prefix, "STR", ap_get_server_banner(),
                       "STR",
                       ap_escape_html(r->pool, ap_get_server_name(r)),
                       "STR", sport,
                       "STR", NULL);
}