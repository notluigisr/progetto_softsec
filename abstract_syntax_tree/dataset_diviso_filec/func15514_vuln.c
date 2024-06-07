static int f_midi_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_midi *midi = func_to_midi(f);
	unsigned i;
	int err;

	
	if (intf != midi->ms_id)
		return 0;

	err = f_midi_start_ep(midi, f, midi->in_ep);
	if (err)
		return err;

	err = f_midi_start_ep(midi, f, midi->out_ep);
	if (err)
		return err;

	
	while (kfifo_avail(&midi->in_req_fifo)) {
		struct usb_request *req =
			midi_alloc_ep_req(midi->in_ep, midi->buflen);

		if (req == NULL)
			return -ENOMEM;

		req->length = 0;
		req->complete = f_midi_complete;

		kfifo_put(&midi->in_req_fifo, req);
	}

	
	for (i = 0; i < midi->qlen && err == 0; i++) {
		struct usb_request *req =
			midi_alloc_ep_req(midi->out_ep, midi->buflen);

		if (req == NULL)
			return -ENOMEM;

		req->complete = f_midi_complete;
		err = usb_ep_queue(midi->out_ep, req, GFP_ATOMIC);
		if (err) {
			ERROR(midi, "STR",
				    midi->out_ep->name, err);
			free_ep_req(midi->out_ep, req);
			return err;
		}
	}

	return 0;
}