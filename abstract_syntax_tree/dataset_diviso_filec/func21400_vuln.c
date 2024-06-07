static void wdm_in_callback(struct urb *urb)
{
	struct wdm_device *desc = urb->context;
	int status = urb->status;

	spin_lock(&desc->iuspin);
	clear_bit(WDM_RESPONDING, &desc->flags);

	if (status) {
		switch (status) {
		case -ENOENT:
			dev_dbg(&desc->intf->dev,
				"STR");
			goto skip_error;
		case -ECONNRESET:
			dev_dbg(&desc->intf->dev,
				"STR");
			goto skip_error;
		case -ESHUTDOWN:
			dev_dbg(&desc->intf->dev,
				"STR");
			goto skip_error;
		case -EPIPE:
			dev_err(&desc->intf->dev,
				"STR");
			break;
		default:
			dev_err(&desc->intf->dev,
				"STR", status);
			break;
		}
	}

	desc->rerr = status;
	desc->reslength = urb->actual_length;
	memmove(desc->ubuf + desc->length, desc->inbuf, desc->reslength);
	desc->length += desc->reslength;
skip_error:
	wake_up(&desc->wait);

	set_bit(WDM_READ, &desc->flags);
	spin_unlock(&desc->iuspin);
}