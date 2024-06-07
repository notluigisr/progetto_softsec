vhost_user_set_log_base(struct virtio_net **pdev, struct VhostUserMsg *msg,
			int main_fd __rte_unused)
{
	struct virtio_net *dev = *pdev;
	int fd = msg->fds[0];
	uint64_t size, off;
	void *addr;

	if (validate_msg_fds(msg, 1) != 0)
		return RTE_VHOST_MSG_RESULT_ERR;

	if (fd < 0) {
		VHOST_LOG_CONFIG(ERR, "STR", fd);
		return RTE_VHOST_MSG_RESULT_ERR;
	}

	if (msg->size != sizeof(VhostUserLog)) {
		VHOST_LOG_CONFIG(ERR,
			"STR",
			msg->size, (int)sizeof(VhostUserLog));
		return RTE_VHOST_MSG_RESULT_ERR;
	}

	size = msg->payload.log.mmap_size;
	off  = msg->payload.log.mmap_offset;

	
	if (off > size) {
		VHOST_LOG_CONFIG(ERR,
			"STR",
			off, size);
		return RTE_VHOST_MSG_RESULT_ERR;
	}

	VHOST_LOG_CONFIG(INFO,
		"STR",
		size, off);

	
	addr = mmap(0, size + off, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	if (addr == MAP_FAILED) {
		VHOST_LOG_CONFIG(ERR, "STR");
		return RTE_VHOST_MSG_RESULT_ERR;
	}

	
	if (dev->log_addr) {
		munmap((void *)(uintptr_t)dev->log_addr, dev->log_size);
	}
	dev->log_addr = (uint64_t)(uintptr_t)addr;
	dev->log_base = dev->log_addr + off;
	dev->log_size = size;

	
	msg->size = 0;
	msg->fd_num = 0;

	return RTE_VHOST_MSG_RESULT_REPLY;
}