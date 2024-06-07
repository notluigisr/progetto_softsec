static void chrc_read_cb(struct gatt_db_attribute *attrib,
					unsigned int id, uint16_t offset,
					uint8_t opcode, struct bt_att *att,
					void *user_data)
{
	struct external_chrc *chrc = user_data;
	struct btd_device *device;

	if (chrc->attrib != attrib) {
		error("STR");
		goto fail;
	}

	device = att_get_device(att);
	if (!device) {
		error("STR");
		goto fail;
	}

	if (send_read(device, attrib, chrc->proxy, chrc->pending_reads, id,
					offset, bt_att_get_link_type(att)))
		return;

fail:
	gatt_db_attribute_read_result(attrib, id, BT_ATT_ERROR_UNLIKELY,
								NULL, 0);
}