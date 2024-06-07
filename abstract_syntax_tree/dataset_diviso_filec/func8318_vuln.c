static struct pending_op *send_write(struct btd_device *device,
					struct gatt_db_attribute *attrib,
					GDBusProxy *proxy,
					struct queue *owner_queue,
					unsigned int id,
					const uint8_t *value, size_t len,
					uint16_t offset, uint8_t link_type,
					bool is_characteristic,
					bool prep_authorize)
{
	struct pending_op *op;

	op = pending_write_new(device, owner_queue, attrib, id, value, len,
					offset, link_type, is_characteristic,
					prep_authorize);

	if (g_dbus_proxy_method_call(proxy, "STR", write_setup_cb,
					owner_queue ? write_reply_cb : NULL,
					op, pending_op_free) == TRUE)
		return op;

	pending_op_free(op);

	return NULL;
}