static ssize_t tower_write (struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
	struct lego_usb_tower *dev;
	size_t bytes_to_write;
	int retval = 0;

	dev = file->private_data;

	
	if (mutex_lock_interruptible(&dev->lock)) {
		retval = -ERESTARTSYS;
		goto exit;
	}

	
	if (dev->udev == NULL) {
		retval = -ENODEV;
		pr_err("STR", retval);
		goto unlock_exit;
	}

	
	if (count == 0) {
		dev_dbg(&dev->udev->dev, "STR");
		goto unlock_exit;
	}

	
	while (dev->interrupt_out_busy) {
		if (file->f_flags & O_NONBLOCK) {
			retval = -EAGAIN;
			goto unlock_exit;
		}
		retval = wait_event_interruptible (dev->write_wait, !dev->interrupt_out_busy);
		if (retval) {
			goto unlock_exit;
		}
	}

	
	bytes_to_write = min_t(int, count, write_buffer_size);
	dev_dbg(&dev->udev->dev, "STR",
		__func__, count, bytes_to_write);

	if (copy_from_user (dev->interrupt_out_buffer, buffer, bytes_to_write)) {
		retval = -EFAULT;
		goto unlock_exit;
	}

	
	usb_fill_int_urb(dev->interrupt_out_urb,
			 dev->udev,
			 usb_sndintpipe(dev->udev, dev->interrupt_out_endpoint->bEndpointAddress),
			 dev->interrupt_out_buffer,
			 bytes_to_write,
			 tower_interrupt_out_callback,
			 dev,
			 dev->interrupt_out_interval);

	dev->interrupt_out_busy = 1;
	wmb();

	retval = usb_submit_urb (dev->interrupt_out_urb, GFP_KERNEL);
	if (retval) {
		dev->interrupt_out_busy = 0;
		dev_err(&dev->udev->dev,
			"STR", retval);
		goto unlock_exit;
	}
	retval = bytes_to_write;

unlock_exit:
	
	mutex_unlock(&dev->lock);

exit:
	return retval;
}