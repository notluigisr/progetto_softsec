static void ms_print_debug_regs(struct rtsx_usb_ms *host)
{
	struct rtsx_ucr *ucr = host->ucr;
	u16 i;
	u8 *ptr;

	
	rtsx_usb_init_cmd(ucr);

	
	for (i = 0xFD40; i <= 0xFD44; i++)
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, i, 0, 0);

	
	for (i = 0xFD51; i <= 0xFD56; i++)
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, i, 0, 0);

	
	for (i = 0xFD60; i <= 0xFD65; i++)
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, i, 0, 0);

	
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_DATA_SOURCE, 0, 0);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_SELECT, 0, 0);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_CLK_EN, 0, 0);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_PWR_CTL, 0, 0);

	rtsx_usb_send_cmd(ucr, MODE_CR, 100);
	rtsx_usb_get_rsp(ucr, 21, 100);

	ptr = ucr->rsp_buf;
	for (i = 0xFD40; i <= 0xFD44; i++)
		dev_dbg(ms_dev(host), "STR", i, *(ptr++));
	for (i = 0xFD51; i <= 0xFD56; i++)
		dev_dbg(ms_dev(host), "STR", i, *(ptr++));
	for (i = 0xFD60; i <= 0xFD65; i++)
		dev_dbg(ms_dev(host), "STR", i, *(ptr++));

	dev_dbg(ms_dev(host), "STR", CARD_DATA_SOURCE, *(ptr++));
	dev_dbg(ms_dev(host), "STR", CARD_SELECT, *(ptr++));
	dev_dbg(ms_dev(host), "STR", CARD_CLK_EN, *(ptr++));
	dev_dbg(ms_dev(host), "STR", CARD_PWR_CTL, *(ptr++));
}