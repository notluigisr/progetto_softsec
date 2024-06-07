static struct pending_op *pending_ccc_new(struct bt_att *att,
					struct gatt_db_attribute *attrib,
					uint16_t value,
					uint8_t link_type)
{
	struct pending_op *op;
	struct btd_device *device;

	device = att_get_device(att);
	if (!device) {
		error("STR");
		return NULL;
	}

	op = new0(struct pending_op, 1);

	op->data.iov_base = UINT_TO_PTR(value);
	op->data.iov_len = sizeof(value);

	op->device = device;
	op->attrib = attrib;
	op->link_type = link_type;

	return op;
}