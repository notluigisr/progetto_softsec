vhost_user_set_postcopy_listen(struct virtio_net **pdev,
			struct VhostUserMsg *msg __rte_unused,
			int main_fd __rte_unused)
{
	struct virtio_net *dev = *pdev;

	if (dev->mem && dev->mem->nregions) {
		RTE_LOG(ERR, VHOST_CONFIG,
			"STR");
		return RTE_VHOST_MSG_RESULT_ERR;
	}
	dev->postcopy_listening = 1;

	return RTE_VHOST_MSG_RESULT_OK;
}