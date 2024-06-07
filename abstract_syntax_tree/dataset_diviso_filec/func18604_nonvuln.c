static ssize_t show_pan_tilt(struct class_device *class_dev, char *buf)
{
	struct pwc_device *pdev = cd_to_pwc(class_dev);
	return sprintf(buf, "STR", pdev->pan_angle, pdev->tilt_angle);
}