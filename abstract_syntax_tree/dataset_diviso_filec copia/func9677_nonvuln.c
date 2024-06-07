static __poll_t port_fops_poll(struct file *filp, poll_table *wait)
{
	struct port *port;
	__poll_t ret;

	port = filp->private_data;
	poll_wait(filp, &port->waitqueue, wait);

	if (!port->guest_connected) {
		
		return EPOLLHUP;
	}
	ret = 0;
	if (!will_read_block(port))
		ret |= EPOLLIN | EPOLLRDNORM;
	if (!will_write_block(port))
		ret |= EPOLLOUT;
	if (!port->host_connected)
		ret |= EPOLLHUP;

	return ret;
}