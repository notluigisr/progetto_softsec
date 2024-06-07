static void stub_shutdown_connection(struct usbip_device *ud)
{
	struct stub_device *sdev = container_of(ud, struct stub_device, ud);

	
	if (ud->tcp_socket) {
		dev_dbg(&sdev->udev->dev, "STR", ud->sockfd);
		kernel_sock_shutdown(ud->tcp_socket, SHUT_RDWR);
	}

	
	if (ud->tcp_rx) {
		kthread_stop_put(ud->tcp_rx);
		ud->tcp_rx = NULL;
	}
	if (ud->tcp_tx) {
		kthread_stop_put(ud->tcp_tx);
		ud->tcp_tx = NULL;
	}

	
	if (ud->tcp_socket) {
		sockfd_put(ud->tcp_socket);
		ud->tcp_socket = NULL;
		ud->sockfd = -1;
	}

	
	stub_device_cleanup_urbs(sdev);

	
	{
		unsigned long flags;
		struct stub_unlink *unlink, *tmp;

		spin_lock_irqsave(&sdev->priv_lock, flags);
		list_for_each_entry_safe(unlink, tmp, &sdev->unlink_tx, list) {
			list_del(&unlink->list);
			kfree(unlink);
		}
		list_for_each_entry_safe(unlink, tmp, &sdev->unlink_free,
					 list) {
			list_del(&unlink->list);
			kfree(unlink);
		}
		spin_unlock_irqrestore(&sdev->priv_lock, flags);
	}
}