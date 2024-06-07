static void url_stream_start (auth_client *auth_user)
{
    char *mount, *server;
    ice_config_t *config = config_get_config ();
    mount_proxy *mountinfo = config_find_mount (config, auth_user->mount, MOUNT_TYPE_NORMAL);
    auth_t *auth = mountinfo->auth;
    auth_url *url = auth->state;
    char *stream_start_url;
    int port;
    char post [4096];

    if (url->stream_start == NULL)
    {
        config_release_config ();
        return;
    }
    server = util_url_escape (config->hostname);
    port = config->port;
    stream_start_url = strdup (url->stream_start);
    
    mountinfo->auth->refcount++;
    config_release_config ();
    mount = util_url_escape (auth_user->mount);

    snprintf (post, sizeof (post),
            "STR", mount, server, port);
    free (server);
    free (mount);

    if (strchr (url->stream_start, '@') == NULL)
    {
        if (url->userpwd)
            curl_easy_setopt (url->handle, CURLOPT_USERPWD, url->userpwd);
        else
            curl_easy_setopt (url->handle, CURLOPT_USERPWD, "");
    }
    else
        curl_easy_setopt (url->handle, CURLOPT_USERPWD, "");
    curl_easy_setopt (url->handle, CURLOPT_URL, stream_start_url);
    curl_easy_setopt (url->handle, CURLOPT_POSTFIELDS, post);
    curl_easy_setopt (url->handle, CURLOPT_WRITEHEADER, auth_user);

    if (curl_easy_perform (url->handle))
        ICECAST_LOG_WARN("STR", stream_start_url, url->errormsg);

    auth_release (auth);
    free (stream_start_url);
    return;
}