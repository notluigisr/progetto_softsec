static bool match_gatt_record(const void *data, const void *user_data)
{
	const struct gatt_record *rec = data;
	const struct gatt_db_attribute *attr = user_data;

	return (rec->attr == attr);
}