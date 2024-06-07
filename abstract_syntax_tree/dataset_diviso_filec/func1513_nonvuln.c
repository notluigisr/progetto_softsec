static void reg_w(struct sd *sd, u16 index, u16 value)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int ret, req = 0;

	if (sd->gspca_dev.usb_err < 0)
		return;

	
	udelay(150);

	switch (sd->bridge) {
	case BRIDGE_OV511:
	case BRIDGE_OV511PLUS:
		req = 2;
		break;
	case BRIDGE_OVFX2:
		req = 0x0a;
		
	case BRIDGE_W9968CF:
		gspca_dbg(gspca_dev, D_USBO, "STR",
			  req, value, index);
		ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			req,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, NULL, 0, 500);
		goto leave;
	default:
		req = 1;
	}

	gspca_dbg(gspca_dev, D_USBO, "STR",
		  req, index, value);
	sd->gspca_dev.usb_buf[0] = value;
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			req,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index,
			sd->gspca_dev.usb_buf, 1, 500);
leave:
	if (ret < 0) {
		gspca_err(gspca_dev, "STR", index, ret);
		sd->gspca_dev.usb_err = ret;
		return;
	}
}