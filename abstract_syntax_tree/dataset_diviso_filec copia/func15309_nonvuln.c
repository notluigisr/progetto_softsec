ex_bunload(exarg_T *eap)
{
    if (ERROR_IF_ANY_POPUP_WINDOW)
	return;
    eap->errmsg = do_bufdel(
	    eap->cmdidx == CMD_bdelete ? DOBUF_DEL
		: eap->cmdidx == CMD_bwipeout ? DOBUF_WIPE
		: DOBUF_UNLOAD, eap->arg,
	    eap->addr_count, (int)eap->line1, (int)eap->line2, eap->forceit);
}