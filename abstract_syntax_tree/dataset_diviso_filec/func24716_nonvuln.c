static void ath6kl_usb_get_default_pipe(struct ath6kl *ar,
					u8 *ul_pipe, u8 *dl_pipe)
{
	*ul_pipe = ATH6KL_USB_PIPE_TX_CTRL;
	*dl_pipe = ATH6KL_USB_PIPE_RX_CTRL;
}