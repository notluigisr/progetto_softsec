static void url_stream_auth (auth_client *auth_user)
{
    ice_config_t *config;
    int port;
    client_t *client = auth_user->client;
    auth_url *url = client->auth->state;
    char *mount, *host, *user, *pass, *ipaddr, *admin="";
    char post [4096];

    if (strchr (url->stream_auth, '@') == NULL)
    {
        if (url->userpwd)
            curl_easy_setopt (url->handle, CURLOPT_USERPWD, url->userpwd);
        else
            curl_easy_setopt (url->handle, CURLOPT_USERPWD, "");
    }
    else
        curl_easy_setopt (url->handle, CURLOPT_USERPWD, "");
    curl_easy_setopt (url->handle, CURLOPT_URL, url->stream_auth);
    curl_easy_setopt (url->handle, CURLOPT_POSTFIELDS, post);
    curl_easy_setopt (url->handle, CURLOPT_WRITEHEADER, auth_user);
    if (strcmp (auth_user->mount, httpp_getvar (client->parser, HTTPP_VAR_URI)) != 0)
        admin = "STR";
    mount = util_url_escape (auth_user->mount);
    config = config_get_config ();
    host = util_url_escape (config->hostname);
    port = config->port;
    config_release_config ();
    ipaddr = util_url_escape (client->con->ip);

    if (client->username) {
        user = util_url_escape(client->username);
    } else {
        user = strdup("");
    }

    if (client->password) {
        pass = util_url_escape(client->password);
    } else {
        pass = strdup("");
    }

    snprintf (post, sizeof (post),
            "STR",
            mount, ipaddr, host, port, user, pass, admin);
    free (ipaddr);
    free (user);
    free (pass);
    free (mount);
    free (host);

    client->authenticated = 0;
    if (curl_easy_perform (url->handle))
        ICECAST_LOG_WARN("STR", url->stream_auth, url->errormsg);
}