static int irda_open_tsap(struct irda_sock *self, __u8 tsap_sel, char *name)
{
	notify_t notify;

	if (self->tsap) {
		IRDA_DEBUG(0, "STR", __func__);
		return -EBUSY;
	}

	
	irda_notify_init(&notify);
	notify.connect_confirm       = irda_connect_confirm;
	notify.connect_indication    = irda_connect_indication;
	notify.disconnect_indication = irda_disconnect_indication;
	notify.data_indication       = irda_data_indication;
	notify.udata_indication	     = irda_data_indication;
	notify.flow_indication       = irda_flow_indication;
	notify.instance = self;
	strncpy(notify.name, name, NOTIFY_MAX_NAME);

	self->tsap = irttp_open_tsap(tsap_sel, DEFAULT_INITIAL_CREDIT,
				     &notify);
	if (self->tsap == NULL) {
		IRDA_DEBUG(0, "STR",
			   __func__);
		return -ENOMEM;
	}
	
	self->stsap_sel = self->tsap->stsap_sel;

	return 0;
}