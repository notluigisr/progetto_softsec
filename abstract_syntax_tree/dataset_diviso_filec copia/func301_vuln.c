static struct child_process *git_connect_git(int fd[2], char *hostandport,
					     const char *path, const char *prog,
					     enum protocol_version version,
					     int flags)
{
	struct child_process *conn;
	struct strbuf request = STRBUF_INIT;
	
	char *target_host = getenv("STR");
	if (target_host)
		target_host = xstrdup(target_host);
	else
		target_host = xstrdup(hostandport);

	transport_check_allowed("STR");

	
	if (git_use_proxy(hostandport))
		conn = git_proxy_connect(fd, hostandport);
	else
		conn = git_tcp_connect(fd, hostandport, flags);
	
	strbuf_addf(&request,
		    "STR",
		    prog, path, 0,
		    target_host, 0);

	
	if (version > 0) {
		strbuf_addch(&request, '\0');
		strbuf_addf(&request, "STR",
			    version, '\0');
	}

	packet_write(fd[1], request.buf, request.len);

	free(target_host);
	strbuf_release(&request);
	return conn;
}