static int xudc_read_fifo(struct xusb_ep *ep, struct xusb_req *req)
{
	u8 *buf;
	u32 is_short, count, bufferspace;
	u8 bufoffset;
	u8 two_pkts = 0;
	int ret;
	int retval = -EAGAIN;
	struct xusb_udc *udc = ep->udc;

	if (ep->buffer0ready && ep->buffer1ready) {
		dev_dbg(udc->dev, "STR");
		return retval;
	}
top:
	if (ep->curbufnum)
		bufoffset = XUSB_EP_BUF1COUNT_OFFSET;
	else
		bufoffset = XUSB_EP_BUF0COUNT_OFFSET;

	count = udc->read_fn(udc->addr + ep->offset + bufoffset);

	if (!ep->buffer0ready && !ep->buffer1ready)
		two_pkts = 1;

	buf = req->usb_req.buf + req->usb_req.actual;
	prefetchw(buf);
	bufferspace = req->usb_req.length - req->usb_req.actual;
	is_short = count < ep->ep_usb.maxpacket;

	if (unlikely(!bufferspace)) {
		
		if (req->usb_req.status != -EOVERFLOW)
			dev_dbg(udc->dev, "STR",
				ep->ep_usb.name, count);
		req->usb_req.status = -EOVERFLOW;
		xudc_done(ep, req, -EOVERFLOW);
		return 0;
	}

	ret = xudc_eptxrx(ep, req, buf, count);
	switch (ret) {
	case 0:
		req->usb_req.actual += min(count, bufferspace);
		dev_dbg(udc->dev, "STR",
			ep->ep_usb.name, count, is_short ? "STR", req,
			req->usb_req.actual, req->usb_req.length);
		bufferspace -= count;
		
		if ((req->usb_req.actual == req->usb_req.length) || is_short) {
			if (udc->dma_enabled && req->usb_req.length)
				dma_sync_single_for_cpu(udc->dev,
							req->usb_req.dma,
							req->usb_req.actual,
							DMA_FROM_DEVICE);
			xudc_done(ep, req, 0);
			return 0;
		}
		if (two_pkts) {
			two_pkts = 0;
			goto top;
		}
		break;
	case -EAGAIN:
		dev_dbg(udc->dev, "STR");
		break;
	case -EINVAL:
	case -ETIMEDOUT:
		
		xudc_done(ep, req, -ECONNRESET);
		retval = 0;
		break;
	}

	return retval;
}