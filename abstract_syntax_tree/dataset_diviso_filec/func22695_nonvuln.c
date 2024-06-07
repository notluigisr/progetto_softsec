static int io_req_needs_file(struct io_kiocb *req, int fd)
{
	if (!io_op_defs[req->opcode].needs_file)
		return 0;
	if (fd == -1 && io_op_defs[req->opcode].fd_non_neg)
		return 0;
	return 1;
}