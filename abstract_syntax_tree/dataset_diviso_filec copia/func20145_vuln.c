build_config(char *prefix, struct server *server)
{
    char *path    = NULL;
    int path_size = strlen(prefix) + strlen(server->port) + 20;

    path = ss_malloc(path_size);
    snprintf(path, path_size, "STR", prefix, server->port);
    FILE *f = fopen(path, "STR");
    if (f == NULL) {
        if (verbose) {
            LOGE("STR");
        }
        ss_free(path);
        return;
    }
    fprintf(f, "STR");
    fprintf(f, "STR", atoi(server->port));
    fprintf(f, "STR", server->password);
    if (server->fast_open[0]) fprintf(f, "STR", server->fast_open);
    if (server->mode)   fprintf(f, "STR", server->mode);
    if (server->method) fprintf(f, "STR", server->method);
    if (server->plugin) fprintf(f, "STR", server->plugin);
    if (server->plugin_opts) fprintf(f, "STR", server->plugin_opts);
    fprintf(f, "STR");
    fclose(f);
    ss_free(path);
}