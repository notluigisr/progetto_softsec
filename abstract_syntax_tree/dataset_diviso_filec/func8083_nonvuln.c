int __sys_connect_file(struct file *file, struct sockaddr __user *uservaddr,
		       int addrlen, int file_flags)
{
	struct socket *sock;
	struct sockaddr_storage address;
	int err;

	sock = sock_from_file(file, &err);
	if (!sock)
		goto out;
	err = move_addr_to_kernel(uservaddr, addrlen, &address);
	if (err < 0)
		goto out;

	err =
	    security_socket_connect(sock, (struct sockaddr *)&address, addrlen);
	if (err)
		goto out;

	err = sock->ops->connect(sock, (struct sockaddr *)&address, addrlen,
				 sock->file->f_flags | file_flags);
out:
	return err;
}