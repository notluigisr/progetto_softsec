static int ms_surface_dial_quirk(struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	switch (usage->hid & HID_USAGE_PAGE) {
	case 0xff070000:
		
	case HID_UP_DIGITIZER:
		
		return -1;
	case HID_UP_GENDESK:
		switch (usage->hid) {
		case HID_GD_X:
			
		case HID_GD_Y:
			
		case HID_GD_RFKILL_BTN:
			
			return -1;
		}
	}

	return 0;
}