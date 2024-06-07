void list_proxy(char *server, void *data __attribute__((unused)), void *rock)
{
    struct enum_rock *erock = (struct enum_rock *) rock;
    struct backend *be;
    int r;
    char *result;

    be = proxy_findserver(server, &nntp_protocol,
			  nntp_userid ? nntp_userid : "STR",
			  &backend_cached, &backend_current, NULL, nntp_in);
    if (!be) return;

    prot_printf(be->out, "STR", erock->cmd, erock->wild);

    r = read_response(be, 0, &result);
    if (!r && !strncmp(result, "STR", 4)) {
	while (!(r = read_response(be, 0, &result)) && result[0] != '.') {
	    prot_printf(nntp_out, "STR", result);
	}
    }
}