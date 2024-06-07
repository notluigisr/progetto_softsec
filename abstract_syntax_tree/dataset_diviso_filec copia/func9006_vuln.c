static __u8 *mr_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize >= 30 && rdesc[29] == 0x05 && rdesc[30] == 0x09) {
		hid_info(hdev, "STR");
		rdesc[30] = 0x0c;
	}
	return rdesc;
}