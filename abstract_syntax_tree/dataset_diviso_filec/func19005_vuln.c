int lg2ff_init(struct hid_device *hid)
{
	struct lg2ff_device *lg2ff;
	struct hid_report *report;
	struct hid_input *hidinput = list_entry(hid->inputs.next,
						struct hid_input, list);
	struct input_dev *dev = hidinput->input;
	int error;

	
	report = hid_validate_values(hid, HID_OUTPUT_REPORT, 0, 0, 7);
	if (!report)
		return -ENODEV;

	lg2ff = kmalloc(sizeof(struct lg2ff_device), GFP_KERNEL);
	if (!lg2ff)
		return -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, lg2ff, play_effect);
	if (error) {
		kfree(lg2ff);
		return error;
	}

	lg2ff->report = report;
	report->field[0]->value[0] = 0xf3;
	report->field[0]->value[1] = 0x00;
	report->field[0]->value[2] = 0x00;
	report->field[0]->value[3] = 0x00;
	report->field[0]->value[4] = 0x00;
	report->field[0]->value[5] = 0x00;
	report->field[0]->value[6] = 0x00;

	hid_hw_request(hid, report, HID_REQ_SET_REPORT);

	hid_info(hid, "STR");

	return 0;
}