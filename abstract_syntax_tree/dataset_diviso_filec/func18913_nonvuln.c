static int pcan_usb_pro_init(struct peak_usb_device *dev)
{
	struct pcan_usb_pro_device *pdev =
			container_of(dev, struct pcan_usb_pro_device, dev);
	struct pcan_usb_pro_interface *usb_if = NULL;
	struct pcan_usb_pro_fwinfo *fi = NULL;
	struct pcan_usb_pro_blinfo *bi = NULL;
	int err;

	
	if (!dev->prev_siblings) {
		
		usb_if = kzalloc(sizeof(struct pcan_usb_pro_interface),
				 GFP_KERNEL);
		fi = kmalloc(sizeof(struct pcan_usb_pro_fwinfo), GFP_KERNEL);
		bi = kmalloc(sizeof(struct pcan_usb_pro_blinfo), GFP_KERNEL);
		if (!usb_if || !fi || !bi) {
			err = -ENOMEM;
			goto err_out;
		}

		
		usb_if->cm_ignore_count = 5;

		
		err = pcan_usb_pro_send_req(dev, PCAN_USBPRO_REQ_INFO,
					    PCAN_USBPRO_INFO_FW,
					    fi, sizeof(*fi));
		if (err) {
			dev_err(dev->netdev->dev.parent,
				"STR",
				pcan_usb_pro.name, err);
			goto err_out;
		}

		err = pcan_usb_pro_send_req(dev, PCAN_USBPRO_REQ_INFO,
					    PCAN_USBPRO_INFO_BL,
					    bi, sizeof(*bi));
		if (err) {
			dev_err(dev->netdev->dev.parent,
				"STR",
				pcan_usb_pro.name, err);
			goto err_out;
		}

		
		err = pcan_usb_pro_drv_loaded(dev, 1);
		if (err)
			goto err_out;

		dev_info(dev->netdev->dev.parent,
		     "STR",
		     pcan_usb_pro.name,
		     bi->hw_rev, bi->serial_num_hi, bi->serial_num_lo,
		     pcan_usb_pro.ctrl_count);
	} else {
		usb_if = pcan_usb_pro_dev_if(dev->prev_siblings);
	}

	pdev->usb_if = usb_if;
	usb_if->dev[dev->ctrl_idx] = dev;

	
	pcan_usb_pro_set_led(dev, 0, 1);

	kfree(bi);
	kfree(fi);

	return 0;

 err_out:
	kfree(bi);
	kfree(fi);
	kfree(usb_if);

	return err;
}