int l2tp_packet_send(int sock, struct l2tp_packet_t *pack)
{
	uint8_t *buf = mempool_alloc(buf_pool);
	struct l2tp_avp_t *avp;
	struct l2tp_attr_t *attr;
	uint8_t *ptr;
	int n;
	int len = sizeof(pack->hdr);

	if (!buf) {
		log_emerg("STR");
		return -1;
	}

	memset(buf, 0, L2TP_MAX_PACKET_SIZE);

	ptr = buf + sizeof(pack->hdr);

	list_for_each_entry(attr, &pack->attrs, entry) {
		if (len + sizeof(*avp) + attr->length >= L2TP_MAX_PACKET_SIZE) {
			log_error("STR");
			mempool_free(buf);
			return -1;
		}
		avp = (struct l2tp_avp_t *)ptr;
		avp->type = htons(attr->attr->id);
		avp->M = attr->M;
		avp->H = attr->H;
		avp->length = sizeof(*avp) + attr->length;
		*(uint16_t *)ptr = htons(*(uint16_t *)ptr);
		if (attr->H)
			memcpy(avp->val, attr->val.octets, attr->length);
		else
			switch (attr->attr->type) {
			case ATTR_TYPE_INT16:
				*(int16_t *)avp->val = htons(attr->val.int16);
				break;
			case ATTR_TYPE_INT32:
				*(int32_t *)avp->val = htonl(attr->val.int32);
				break;
			case ATTR_TYPE_INT64:
				*(uint64_t *)avp->val = htobe64(attr->val.uint64);
				break;
			case ATTR_TYPE_STRING:
			case ATTR_TYPE_OCTETS:
				memcpy(avp->val, attr->val.string, attr->length);
				break;
			}
		ptr += sizeof(*avp) + attr->length;
		len += sizeof(*avp) + attr->length;
	}

	pack->hdr.length = htons(len);
	memcpy(buf, &pack->hdr, sizeof(pack->hdr));

	n = sendto(sock, buf, ntohs(pack->hdr.length), 0,
		   &pack->addr, sizeof(pack->addr));
	mempool_free(buf);

	if (n < 0) {
		if (errno == EAGAIN) {
			if (conf_verbose)
				log_warn("STR");
		} else {
			if (conf_verbose)
				log_warn("STR", strerror(errno));
			return -1;
		}
	}

	if (n != ntohs(pack->hdr.length)) {
		if (conf_verbose)
			log_warn("STR", n, ntohs(pack->hdr.length));
	}

	return 0;
}