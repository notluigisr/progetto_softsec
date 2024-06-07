static void brcmf_msgbuf_rxbuf_ioctlresp_post(struct brcmf_msgbuf *msgbuf)
{
	u32 count;

	count = msgbuf->max_ioctlrespbuf - msgbuf->cur_ioctlrespbuf;
	count = brcmf_msgbuf_rxbuf_ctrl_post(msgbuf, false, count);
	msgbuf->cur_ioctlrespbuf += count;
}