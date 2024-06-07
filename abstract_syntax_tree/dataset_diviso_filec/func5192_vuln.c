static struct pending_op *pending_write_new(struct btd_device *device,
					struct queue *owner_queue,
					struct gatt_db_attribute *attrib,
					unsigned int id,
					const uint8_t *value, size_t len,
					uint16_t offset, uint8_t link_type,
					bool is_characteristic,
					bool prep_authorize)
{
	struct pending_op *op;

	op = new0(struct pending_op, 1);

	op->data.iov_base = (uint8_t *) value;
	op->data.iov_len = len;

	op->device = device;
	op->owner_queue = owner_queue;
	op->attrib = attrib;
	op->id = id;
	op->offset = offset;
	op->link_type = link_type;
	op->is_characteristic = is_characteristic;
	op->prep_authorize = prep_authorize;
	queue_push_tail(owner_queue, op);

	return op;
}