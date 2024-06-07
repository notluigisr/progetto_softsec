static inline void io_req_put_rsrc(struct io_kiocb *req)
{
	if (req->rsrc_node)
		io_rsrc_put_node(req->rsrc_node, 1);
}