static const struct usb_cdc_union_desc *
ims_pcu_get_cdc_union_desc(struct usb_interface *intf)
{
	const void *buf = intf->altsetting->extra;
	size_t buflen = intf->altsetting->extralen;
	struct usb_cdc_union_desc *union_desc;

	if (!buf) {
		dev_err(&intf->dev, "STR");
		return NULL;
	}

	if (!buflen) {
		dev_err(&intf->dev, "STR");
		return NULL;
	}

	while (buflen > 0) {
		union_desc = (struct usb_cdc_union_desc *)buf;

		if (union_desc->bDescriptorType == USB_DT_CS_INTERFACE &&
		    union_desc->bDescriptorSubType == USB_CDC_UNION_TYPE) {
			dev_dbg(&intf->dev, "STR");
			return union_desc;
		}

		buflen -= union_desc->bLength;
		buf += union_desc->bLength;
	}

	dev_err(&intf->dev, "STR");
	return NULL;