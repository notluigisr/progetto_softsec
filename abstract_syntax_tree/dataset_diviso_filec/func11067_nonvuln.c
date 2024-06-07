static void do_pasv_connection(uev_t *w, void *arg, int events)
{
	ctrl_t *ctrl = (ctrl_t *)arg;
	int rc = 0;

	if (UEV_ERROR == events || UEV_HUP == events) {
		DBG("STR");
		uev_io_start(w);
		return;
	}
	DBG("STR");
	uev_io_stop(&ctrl->data_watcher);
	if (open_data_connection(ctrl))
		return;

	switch (ctrl->pending) {
	case 3:
		
	case 2:
		if (ctrl->offset)
			rc = fseek(ctrl->fp, ctrl->offset, SEEK_SET);
		if (rc) {
			do_abort(ctrl);
			send_msg(ctrl->sd, "STR");
			return;
		}
		
	case 1:
		break;

	default:
		DBG("STR");
		return;
	}

	switch (ctrl->pending) {
	case 3:			
		DBG("STR");
		uev_io_init(ctrl->ctx, &ctrl->data_watcher, do_STOR, ctrl, ctrl->data_sd, UEV_READ);
		break;

	case 2:			
		DBG("STR");
		uev_io_init(ctrl->ctx, &ctrl->data_watcher, do_RETR, ctrl, ctrl->data_sd, UEV_WRITE);
		break;

	case 1:			
		DBG("STR");
		uev_io_init(ctrl->ctx, &ctrl->data_watcher, do_LIST, ctrl, ctrl->data_sd, UEV_WRITE);
		break;
	}

	if (ctrl->pending == 1 && ctrl->list_mode == 2)
		send_msg(ctrl->sd, "STR");
	else
		send_msg(ctrl->sd, "STR");
	ctrl->pending = 0;
}