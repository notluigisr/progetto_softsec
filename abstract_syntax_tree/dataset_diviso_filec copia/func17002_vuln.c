static int pwc_video_close(struct inode *inode, struct file *file)
{
	struct video_device *vdev = file->private_data;
	struct pwc_device *pdev;
	int i;

	PWC_DEBUG_OPEN("STR", vdev);

	pdev = (struct pwc_device *)vdev->priv;
	if (pdev->vopen == 0)
		PWC_DEBUG_MODULE("STR");

	
	if (pdev->vframe_count > 20)
		PWC_DEBUG_MODULE("STR", pdev->vframe_count, pdev->vframes_dumped, pdev->vframes_error);

	if (DEVICE_USE_CODEC1(pdev->type))
	    pwc_dec1_exit();
	else
	    pwc_dec23_exit();

	pwc_isoc_cleanup(pdev);
	pwc_free_buffers(pdev);

	
	if (pdev->error_status != EPIPE) {
		
		if (pwc_set_leds(pdev, 0, 0) < 0)
			PWC_DEBUG_MODULE("STR");
		if (power_save) {
			i = pwc_camera_power(pdev, 0);
			if (i < 0)
				PWC_ERROR("STR", i);
		}
	}
	pdev->vopen--;
	PWC_DEBUG_OPEN("STR", pdev->vopen);
	return 0;
}