static void cpia2_usb_disconnect(struct usb_interface *intf)
{
	struct camera_data *cam = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);

	DBG("STR");
	cpia2_usb_stream_stop(cam);

	mutex_lock(&cam->v4l2_lock);
	DBG("STR");
	cpia2_unregister_camera(cam);
	v4l2_device_disconnect(&cam->v4l2_dev);
	mutex_unlock(&cam->v4l2_lock);
	v4l2_device_put(&cam->v4l2_dev);

	if(cam->buffers) {
		DBG("STR");
		cam->curbuff->status = FRAME_READY;
		cam->curbuff->length = 0;
		wake_up_interruptible(&cam->wq_stream);
	}

	LOG("STR");
}