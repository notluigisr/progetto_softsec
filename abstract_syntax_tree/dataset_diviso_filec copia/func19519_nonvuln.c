static void success_and_wakeup(void)
{
	generic_success();
	cont->redo();
}