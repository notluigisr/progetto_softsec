static ssize_t usbip_sockfd_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct stub_device *sdev = dev_get_drvdata(dev);
	int sockfd = 0;
	struct socket *socket;
	int rv;

	if (!sdev) {
		dev_err(dev, "STR");
		return -ENODEV;
	}

	rv = sscanf(buf, "STR", &sockfd);
	if (rv != 1)
		return -EINVAL;

	if (sockfd != -1) {
		int err;

		dev_info(dev, "STR");

		spin_lock_irq(&sdev->ud.lock);

		if (sdev->ud.status != SDEV_ST_AVAILABLE) {
			dev_err(dev, "STR");
			goto err;
		}

		socket = sockfd_lookup(sockfd, &err);
		if (!socket) {
			dev_err(dev, "STR");
			goto err;
		}

		if (socket->type != SOCK_STREAM) {
			dev_err(dev, "STR",
				socket->type);
			goto sock_err;
		}

		sdev->ud.tcp_socket = socket;
		sdev->ud.sockfd = sockfd;

		spin_unlock_irq(&sdev->ud.lock);

		sdev->ud.tcp_rx = kthread_get_run(stub_rx_loop, &sdev->ud,
						  "STR");
		sdev->ud.tcp_tx = kthread_get_run(stub_tx_loop, &sdev->ud,
						  "STR");

		spin_lock_irq(&sdev->ud.lock);
		sdev->ud.status = SDEV_ST_USED;
		spin_unlock_irq(&sdev->ud.lock);

	} else {
		dev_info(dev, "STR");

		spin_lock_irq(&sdev->ud.lock);
		if (sdev->ud.status != SDEV_ST_USED)
			goto err;

		spin_unlock_irq(&sdev->ud.lock);

		usbip_event_add(&sdev->ud, SDEV_EVENT_DOWN);
	}

	return count;

sock_err:
	sockfd_put(socket);
err:
	spin_unlock_irq(&sdev->ud.lock);
	return -EINVAL;
}