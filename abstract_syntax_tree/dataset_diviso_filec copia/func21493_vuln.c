process_open(u_int32_t id)
{
	u_int32_t pflags;
	Attrib a;
	char *name;
	int r, handle, fd, flags, mode, status = SSH2_FX_FAILURE;

	if ((r = sshbuf_get_cstring(iqueue, &name, NULL)) != 0 ||
	    (r = sshbuf_get_u32(iqueue, &pflags)) != 0 || 
	    (r = decode_attrib(iqueue, &a)) != 0)
		fatal("STR", __func__, ssh_err(r));

	debug3("STR", id, pflags);
	flags = flags_from_portable(pflags);
	mode = (a.flags & SSH2_FILEXFER_ATTR_PERMISSIONS) ? a.perm : 0666;
	logit("STR",
	    name, string_from_portable(pflags), mode);
	if (readonly &&
	    ((flags & O_ACCMODE) == O_WRONLY ||
	    (flags & O_ACCMODE) == O_RDWR)) {
		verbose("STR");
		status = SSH2_FX_PERMISSION_DENIED;
	} else {
		fd = open(name, flags, mode);
		if (fd < 0) {
			status = errno_to_portable(errno);
		} else {
			handle = handle_new(HANDLE_FILE, name, fd, flags, NULL);
			if (handle < 0) {
				close(fd);
			} else {
				send_handle(id, handle);
				status = SSH2_FX_OK;
			}
		}
	}
	if (status != SSH2_FX_OK)
		send_status(id, status);
	free(name);
}