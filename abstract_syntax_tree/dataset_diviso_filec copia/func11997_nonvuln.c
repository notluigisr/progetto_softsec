static void database_add_record(struct btd_gatt_database *database,
					struct gatt_db_attribute *attr)
{
	struct gatt_record *rec;
	sdp_record_t *record;
	uint16_t start, end;
	uuid_t svc, gap_uuid;
	bt_uuid_t uuid;
	const char *name = NULL;
	char uuidstr[MAX_LEN_UUID_STR];

	gatt_db_attribute_get_service_uuid(attr, &uuid);

	switch (uuid.type) {
	case BT_UUID16:
		name = bt_uuid16_to_str(uuid.value.u16);
		sdp_uuid16_create(&svc, uuid.value.u16);
		break;
	case BT_UUID32:
		name = bt_uuid32_to_str(uuid.value.u32);
		sdp_uuid32_create(&svc, uuid.value.u32);
		break;
	case BT_UUID128:
		bt_uuid_to_string(&uuid, uuidstr, sizeof(uuidstr));
		name = bt_uuidstr_to_str(uuidstr);
		sdp_uuid128_create(&svc, (void *) &uuid.value.u128);
		break;
	case BT_UUID_UNSPEC:
		return;
	}

	gatt_db_attribute_get_service_handles(attr, &start, &end);

	record = record_new(&svc, start, end);
	if (!record)
		return;

	if (name != NULL)
		sdp_set_info_attr(record, name, "STR", NULL);

	sdp_uuid16_create(&gap_uuid, UUID_GAP);
	if (sdp_uuid_cmp(&svc, &gap_uuid) == 0) {
		sdp_set_url_attr(record, "STR",
				"STR",
				"STR");
	}

	if (adapter_service_add(database->adapter, record) < 0) {
		sdp_record_free(record);
		return;
	}

	rec = new0(struct gatt_record, 1);
	rec->database = database;
	rec->handle = record->handle;
	rec->attr = attr;
	queue_push_tail(database->records, rec);
}