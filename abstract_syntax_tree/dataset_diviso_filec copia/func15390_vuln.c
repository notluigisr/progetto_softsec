static void stub_recv_cmd_submit(struct stub_device *sdev,
				 struct usbip_header *pdu)
{
	int ret;
	struct stub_priv *priv;
	struct usbip_device *ud = &sdev->ud;
	struct usb_device *udev = sdev->udev;
	int pipe = get_pipe(sdev, pdu->base.ep, pdu->base.direction);

	if (pipe == -1)
		return;

	priv = stub_priv_alloc(sdev, pdu);
	if (!priv)
		return;

	
	if (usb_pipeisoc(pipe))
		priv->urb = usb_alloc_urb(pdu->u.cmd_submit.number_of_packets,
					  GFP_KERNEL);
	else
		priv->urb = usb_alloc_urb(0, GFP_KERNEL);

	if (!priv->urb) {
		usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
		return;
	}

	
	if (pdu->u.cmd_submit.transfer_buffer_length > 0) {
		priv->urb->transfer_buffer =
			kzalloc(pdu->u.cmd_submit.transfer_buffer_length,
				GFP_KERNEL);
		if (!priv->urb->transfer_buffer) {
			usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
			return;
		}
	}

	
	priv->urb->setup_packet = kmemdup(&pdu->u.cmd_submit.setup, 8,
					  GFP_KERNEL);
	if (!priv->urb->setup_packet) {
		dev_err(&udev->dev, "STR");
		usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
		return;
	}

	
	priv->urb->context                = (void *) priv;
	priv->urb->dev                    = udev;
	priv->urb->pipe                   = pipe;
	priv->urb->complete               = stub_complete;

	usbip_pack_pdu(pdu, priv->urb, USBIP_CMD_SUBMIT, 0);


	if (usbip_recv_xbuff(ud, priv->urb) < 0)
		return;

	if (usbip_recv_iso(ud, priv->urb) < 0)
		return;

	
	tweak_special_requests(priv->urb);

	masking_bogus_flags(priv->urb);
	
	ret = usb_submit_urb(priv->urb, GFP_KERNEL);

	if (ret == 0)
		usbip_dbg_stub_rx("STR",
				  pdu->base.seqnum);
	else {
		dev_err(&udev->dev, "STR", ret);
		usbip_dump_header(pdu);
		usbip_dump_urb(priv->urb);

		
		usbip_event_add(ud, SDEV_EVENT_ERROR_SUBMIT);
	}

	usbip_dbg_stub_rx("STR");
}