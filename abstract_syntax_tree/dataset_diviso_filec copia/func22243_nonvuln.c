static int ui_close(UI *ui)
	{
	return UI_method_get_closer(UI_OpenSSL())(ui);
	}