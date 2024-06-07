static struct pending_op *pending_read_new(struct btd_device *device,
					struct queue *owner_queue,
					struct gatt_db_attribute *attrib,
					unsigned int id, uint16_t offset,
					uint8_t link_type)
{
	struct pending_op *op;

	op = new0(struct pending_op, 1);

	op->owner_queue = owner_queue;
	op->device = device;
	op->attrib = attrib;
	op->id = id;
	op->offset = offset;
	op->link_type = link_type;
	queue_push_tail(owner_queue, op);

	return op;
}