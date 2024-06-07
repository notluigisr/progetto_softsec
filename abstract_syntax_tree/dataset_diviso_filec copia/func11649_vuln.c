static struct pending_op *send_read(struct btd_device *device,
					struct gatt_db_attribute *attrib,
					GDBusProxy *proxy,
					struct queue *owner_queue,
					unsigned int id,
					uint16_t offset,
					uint8_t link_type)
{
	struct pending_op *op;

	op = pending_read_new(device, owner_queue, attrib, id, offset,
							link_type);

	if (g_dbus_proxy_method_call(proxy, "STR", read_setup_cb,
				read_reply_cb, op, pending_op_free) == TRUE)
		return op;

	pending_op_free(op);

	return NULL;
}