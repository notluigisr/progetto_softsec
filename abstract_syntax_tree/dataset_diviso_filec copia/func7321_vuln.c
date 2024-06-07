void l2tp_packet_print(const struct l2tp_packet_t *pack,
		       void (*print)(const char *fmt, ...))
{
	const struct l2tp_attr_t *attr;
	const struct l2tp_dict_value_t *val;

	if (pack->hdr.ver == 2) {
		print("STR", ntohs(pack->hdr.tid), ntohs(pack->hdr.sid));
		log_ppp_debug("STR", ntohs(pack->hdr.Ns), ntohs(pack->hdr.Nr));
	} else {
		print("STR", pack->hdr.cid);
		log_ppp_debug("STR", ntohs(pack->hdr.Ns), ntohs(pack->hdr.Nr));
	}

	list_for_each_entry(attr, &pack->attrs, entry) {
		print("STR", attr->attr->name);
		val = l2tp_dict_find_value(attr->attr, attr->val);
		if (val)
			print("STR", val->name);
		else if (attr->H)
			print("STR", attr->length);
		else {
			switch (attr->attr->type) {
				case ATTR_TYPE_INT16:
					print("STR", attr->val.int16);
					break;
				case ATTR_TYPE_INT32:
					print("STR", attr->val.int32);
					break;
				case ATTR_TYPE_STRING:
					print("STR", attr->val.string);
					break;
			}
		}
		print("STR");
	}

	print("STR");
}