static void ndp_msg_init(struct ndp_msg *msg, enum ndp_msg_type msg_type)
{
	size_t raw_struct_size = ndp_msg_type_info(msg_type)->raw_struct_size;

	ndp_msg_type_set(msg, msg_type);
	msg->len = raw_struct_size;
	msg->opts_start = msg->buf + raw_struct_size;

	
	msg->nd_msg.generic.dataptr = ndp_msg_payload(msg);
}