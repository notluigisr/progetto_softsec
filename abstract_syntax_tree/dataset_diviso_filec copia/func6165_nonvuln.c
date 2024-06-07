int rdma_addr_size_kss(struct __kernel_sockaddr_storage *addr)
{
	int ret = rdma_addr_size((struct sockaddr *) addr);

	return ret <= sizeof(*addr) ? ret : 0;
}