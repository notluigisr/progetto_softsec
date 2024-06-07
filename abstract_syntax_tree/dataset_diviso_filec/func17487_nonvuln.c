static ssize_t btd_adapter_pin_cb_iter_next(
					struct btd_adapter_pin_cb_iter *iter,
					struct btd_adapter *adapter,
					struct btd_device *device,
					char *pin_buf, bool *display)
{
	btd_adapter_pin_cb_t cb;
	ssize_t ret;

	while (iter->it != NULL) {
		cb = iter->it->data;
		ret = cb(adapter, device, pin_buf, display, iter->attempt);
		iter->attempt++;
		if (ret > 0)
			return ret;
		iter->attempt = 1;
		iter->it = g_slist_next(iter->it);
	}
	iter->attempt = 0;

	return 0;
}