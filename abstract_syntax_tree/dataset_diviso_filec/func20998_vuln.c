vhost_user_set_log_base(struct virtio_net **pdev, struct VhostUserMsg *msg,
			int main_fd __rte_unused)
{
	struct virtio_net *dev = *pdev;
	int fd = msg->fds[0];
	uint64_t size, off;
	void *addr;

	if (fd < 0) {
		RTE_LOG(ERR, VHOST_CONFIG, "STR", fd);
		return RTE_VHOST_MSG_RESULT_ERR;
	}

	if (msg->size != sizeof(VhostUserLog)) {
		RTE_LOG(ERR, VHOST_CONFIG,
			"STR",
			msg->size, (int)sizeof(VhostUserLog));
		return RTE_VHOST_MSG_RESULT_ERR;
	}

	size = msg->payload.log.mmap_size;
	off  = msg->payload.log.mmap_offset;

	
	if (off > size) {
		RTE_LOG(ERR, VHOST_CONFIG,
			"STR",
			off, size);
		return RTE_VHOST_MSG_RESULT_ERR;
	}

	RTE_LOG(INFO, VHOST_CONFIG,
		"STR",
		size, off);

	
	addr = mmap(0, size + off, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	if (addr == MAP_FAILED) {
		RTE_LOG(ERR, VHOST_CONFIG, "STR");
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