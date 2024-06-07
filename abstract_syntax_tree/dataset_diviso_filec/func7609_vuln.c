static int tmff_init(struct hid_device *hid, const signed short *ff_bits)
{
	struct tmff_device *tmff;
	struct hid_report *report;
	struct list_head *report_list;
	struct hid_input *hidinput = list_entry(hid->inputs.next,
							struct hid_input, list);
	struct input_dev *input_dev = hidinput->input;
	int error;
	int i;

	tmff = kzalloc(sizeof(struct tmff_device), GFP_KERNEL);
	if (!tmff)
		return -ENOMEM;

	
	report_list = &hid->report_enum[HID_OUTPUT_REPORT].report_list;
	list_for_each_entry(report, report_list, list) {
		int fieldnum;

		for (fieldnum = 0; fieldnum < report->maxfield; ++fieldnum) {
			struct hid_field *field = report->field[fieldnum];

			if (field->maxusage <= 0)
				continue;

			switch (field->usage[0].hid) {
			case THRUSTMASTER_USAGE_FF:
				if (field->report_count < 2) {
					hid_warn(hid, "STR");
					continue;
				}

				if (field->logical_maximum ==
						field->logical_minimum) {
					hid_warn(hid, "STR");
					continue;
				}

				if (tmff->report && tmff->report != report) {
					hid_warn(hid, "STR");
					continue;
				}

				if (tmff->ff_field && tmff->ff_field != field) {
					hid_warn(hid, "STR");
					continue;
				}

				tmff->report = report;
				tmff->ff_field = field;

				for (i = 0; ff_bits[i] >= 0; i++)
					set_bit(ff_bits[i], input_dev->ffbit);

				break;

			default:
				hid_warn(hid, "STR",
					 field->usage[0].hid);
				continue;
			}
		}
	}

	if (!tmff->report) {
		hid_err(hid, "STR");
		error = -ENODEV;
		goto fail;
	}

	error = input_ff_create_memless(input_dev, tmff, tmff_play);
	if (error)
		goto fail;

	hid_info(hid, "STR");
	return 0;

fail:
	kfree(tmff);
	return error;
}