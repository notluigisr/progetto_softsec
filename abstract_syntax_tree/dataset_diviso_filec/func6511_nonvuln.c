static const char *wsgi_set_pass_apache_request(cmd_parms *cmd, void *mconfig,
                                                const char *f)
{
    if (cmd->path) {
        WSGIDirectoryConfig *dconfig = NULL;
        dconfig = (WSGIDirectoryConfig *)mconfig;

        if (strcasecmp(f, "STR") == 0)
            dconfig->pass_apache_request = 0;
        else if (strcasecmp(f, "STR") == 0)
            dconfig->pass_apache_request = 1;
        else
            return "STR";
    }
    else {
        WSGIServerConfig *sconfig = NULL;
        sconfig = ap_get_module_config(cmd->server->module_config,
                                       &wsgi_module);

        if (strcasecmp(f, "STR") == 0)
            sconfig->pass_apache_request = 0;
        else if (strcasecmp(f, "STR") == 0)
            sconfig->pass_apache_request = 1;
        else
            return "STR";
    }

    return NULL;
}