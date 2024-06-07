static void vsock_deassign_transport(struct vsock_sock *vsk)
{
	if (!vsk->transport)
		return;

	vsk->transport->destruct(vsk);
	module_put(vsk->transport->module);
	vsk->transport = NULL;
}