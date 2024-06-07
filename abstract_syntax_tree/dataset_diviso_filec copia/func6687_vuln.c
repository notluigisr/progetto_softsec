static void xudc_set_clear_feature(struct xusb_udc *udc)
{
	struct xusb_ep *ep0	= &udc->ep[0];
	struct xusb_req *req	= udc->req;
	struct xusb_ep *target_ep;
	u8 endpoint;
	u8 outinbit;
	u32 epcfgreg;
	int flag = (udc->setup.bRequest == USB_REQ_SET_FEATURE ? 1 : 0);
	int ret;

	switch (udc->setup.bRequestType) {
	case USB_RECIP_DEVICE:
		switch (udc->setup.wValue) {
		case USB_DEVICE_TEST_MODE:
			
			break;
		case USB_DEVICE_REMOTE_WAKEUP:
			if (flag)
				udc->remote_wkp = 1;
			else
				udc->remote_wkp = 0;
			break;
		default:
			xudc_ep0_stall(udc);
			break;
		}
		break;
	case USB_RECIP_ENDPOINT:
		if (!udc->setup.wValue) {
			endpoint = udc->setup.wIndex & USB_ENDPOINT_NUMBER_MASK;
			target_ep = &udc->ep[endpoint];
			outinbit = udc->setup.wIndex & USB_ENDPOINT_DIR_MASK;
			outinbit = outinbit >> 7;

			
			if (outinbit != target_ep->is_in) {
				xudc_ep0_stall(udc);
				return;
			}
			epcfgreg = udc->read_fn(udc->addr + target_ep->offset);
			if (!endpoint) {
				
				epcfgreg &= ~XUSB_EP_CFG_STALL_MASK;
				udc->write_fn(udc->addr,
					      target_ep->offset, epcfgreg);
			} else {
				if (flag) {
					epcfgreg |= XUSB_EP_CFG_STALL_MASK;
					udc->write_fn(udc->addr,
						      target_ep->offset,
						      epcfgreg);
				} else {
					
					epcfgreg &= ~(XUSB_EP_CFG_STALL_MASK |
						XUSB_EP_CFG_DATA_TOGGLE_MASK);
					udc->write_fn(udc->addr,
						      target_ep->offset,
						      epcfgreg);
				}
			}
		}
		break;
	default:
		xudc_ep0_stall(udc);
		return;
	}

	req->usb_req.length = 0;
	ret = __xudc_ep0_queue(ep0, req);
	if (ret == 0)
		return;

	dev_err(udc->dev, "STR");
	xudc_ep0_stall(udc);
}