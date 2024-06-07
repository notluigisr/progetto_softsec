ptp_unpack_OPL (PTPParams *params, unsigned char* data, MTPProperties **pprops, unsigned int len)
{ 
	uint32_t prop_count = dtoh32a(data);
	MTPProperties *props = NULL;
	unsigned int offset = 0, i;

	*pprops = NULL;
	if (prop_count == 0)
		return 0;
	if (prop_count >= INT_MAX/sizeof(MTPProperties)) {
		ptp_debug (params ,"STR", prop_count);
		return 0;
	}
	ptp_debug (params ,"STR", len, prop_count);
	data += sizeof(uint32_t);
	len -= sizeof(uint32_t);
	props = malloc(prop_count * sizeof(MTPProperties));
	if (!props) return 0;
	for (i = 0; i < prop_count; i++) {
		if (len <= 0) {
			ptp_debug (params ,"STR", i, prop_count);
			ptp_debug (params ,"STR");
			ptp_debug (params ,"STR", i);
			qsort (props, i, sizeof(MTPProperties),_compare_func);
			*pprops = props;
			return i;
		}
		props[i].ObjectHandle = dtoh32a(data);
		data += sizeof(uint32_t);
		len -= sizeof(uint32_t);

		props[i].property = dtoh16a(data);
		data += sizeof(uint16_t);
		len -= sizeof(uint16_t);

		props[i].datatype = dtoh16a(data);
		data += sizeof(uint16_t);
		len -= sizeof(uint16_t);

		offset = 0;
		if (!ptp_unpack_DPV(params, data, &offset, len, &props[i].propval, props[i].datatype)) {
			ptp_debug (params ,"STR", i);
			qsort (props, i, sizeof(MTPProperties),_compare_func);
			*pprops = props;
			return i;
		}
		data += offset;
		len -= offset;
	}
	qsort (props, prop_count, sizeof(MTPProperties),_compare_func);
	*pprops = props;
	return prop_count;
}