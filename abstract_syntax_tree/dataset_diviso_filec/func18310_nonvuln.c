static void hif_start(struct ath6kl *ar)
{
	struct ath6kl_usb *device = ath6kl_usb_priv(ar);
	int i;

	ath6kl_usb_start_recv_pipes(device);

	
	for (i = ATH6KL_USB_PIPE_TX_CTRL;
	     i <= ATH6KL_USB_PIPE_TX_DATA_HP; i++) {
		device->pipes[i].urb_cnt_thresh =
		    device->pipes[i].urb_alloc / 2;
	}
}