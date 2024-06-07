static void gap_car_read_cb(struct gatt_db_attribute *attrib,
					unsigned int id, uint16_t offset,
					uint8_t opcode, struct bt_att *att,
					void *user_data)
{
	uint8_t value = 0x01;

	DBG("STR");

	gatt_db_attribute_read_result(attrib, id, 0, &value, sizeof(value));
}