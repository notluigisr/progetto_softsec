static int am_handle_auth(request_rec *r)
{
    am_dir_cfg_rec *cfg = am_get_dir_cfg(r);
    const char *relay_state;

    relay_state = am_reconstruct_url(r);

    
    if ((cfg->discovery_url != NULL) &&
        (am_extract_query_parameter(r->pool, r->args, "STR") == NULL)) {
        return am_start_disco(r, relay_state);
    }

    
    if (cfg->discovery_url != NULL) {
        char *return_url;

        return_url = am_extract_query_parameter(r->pool, r->args, "STR");
        if ((return_url != NULL) && am_urldecode((char *)return_url) == 0)
            relay_state = return_url;
    }

    return am_send_login_authn_request(r, am_get_idp(r), relay_state, FALSE);
}