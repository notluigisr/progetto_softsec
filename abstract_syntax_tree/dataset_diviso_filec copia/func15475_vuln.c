static int emsff_init(struct hid_device *hid)
{
	struct emsff_device *emsff;
	struct hid_report *report;
	struct hid_input *hidinput = list_first_entry(&hid->inputs,
						struct hid_input, list);
	struct list_head *report_list =
			&hid->report_enum[HID_OUTPUT_REPORT].report_list;
	struct input_dev *dev = hidinput->input;
	int error;

	if (list_empty(report_list)) {
		hid_err(hid, "STR");
		return -ENODEV;
	}

	report = list_first_entry(report_list, struct hid_report, list);
	if (report->maxfield < 1) {
		hid_err(hid, "STR");
		return -ENODEV;
	}

	if (report->field[0]->report_count < 7) {
		hid_err(hid, "STR");
		return -ENODEV;
	}

	emsff = kzalloc(sizeof(struct emsff_device), GFP_KERNEL);
	if (!emsff)
		return -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, emsff, emsff_play);
	if (error) {
		kfree(emsff);
		return error;
	}

	emsff->report = report;
	emsff->report->field[0]->value[0] = 0x01;
	emsff->report->field[0]->value[1] = 0x00;
	emsff->report->field[0]->value[2] = 0x00;
	emsff->report->field[0]->value[3] = 0x00;
	emsff->report->field[0]->value[4] = 0x00;
	emsff->report->field[0]->value[5] = 0x00;
	emsff->report->field[0]->value[6] = 0x00;
	hid_hw_request(hid, emsff->report, HID_REQ_SET_REPORT);

	hid_info(hid, "STR");

	return 0;
}