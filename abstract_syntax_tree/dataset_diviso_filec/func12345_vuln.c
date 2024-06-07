static int holtekff_init(struct hid_device *hid)
{
	struct holtekff_device *holtekff;
	struct hid_report *report;
	struct hid_input *hidinput = list_entry(hid->inputs.next,
						struct hid_input, list);
	struct list_head *report_list =
			&hid->report_enum[HID_OUTPUT_REPORT].report_list;
	struct input_dev *dev = hidinput->input;
	int error;

	if (list_empty(report_list)) {
		hid_err(hid, "STR");
		return -ENODEV;
	}

	report = list_entry(report_list->next, struct hid_report, list);

	if (report->maxfield < 1 || report->field[0]->report_count != 7) {
		hid_err(hid, "STR");
		return -ENODEV;
	}

	holtekff = kzalloc(sizeof(*holtekff), GFP_KERNEL);
	if (!holtekff)
		return -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	holtekff->field = report->field[0];

	
	holtekff_send(holtekff, hid, stop_all4);
	holtekff_send(holtekff, hid, stop_all6);

	error = input_ff_create_memless(dev, holtekff, holtekff_play);
	if (error) {
		kfree(holtekff);
		return error;
	}

	hid_info(hid, "STR");

	return 0;
}