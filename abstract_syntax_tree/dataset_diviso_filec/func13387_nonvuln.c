static int input_handle_abs_event(struct input_dev *dev,
				  unsigned int code, int *pval)
{
	struct input_mt *mt = dev->mt;
	bool is_mt_event;
	int *pold;

	if (code == ABS_MT_SLOT) {
		
		if (mt && *pval >= 0 && *pval < mt->num_slots)
			mt->slot = *pval;

		return INPUT_IGNORE_EVENT;
	}

	is_mt_event = input_is_mt_value(code);

	if (!is_mt_event) {
		pold = &dev->absinfo[code].value;
	} else if (mt) {
		pold = &mt->slots[mt->slot].abs[code - ABS_MT_FIRST];
	} else {
		
		pold = NULL;
	}

	if (pold) {
		*pval = input_defuzz_abs_event(*pval, *pold,
						dev->absinfo[code].fuzz);
		if (*pold == *pval)
			return INPUT_IGNORE_EVENT;

		*pold = *pval;
	}

	
	if (is_mt_event && mt && mt->slot != input_abs_get_val(dev, ABS_MT_SLOT)) {
		input_abs_set_val(dev, ABS_MT_SLOT, mt->slot);
		return INPUT_PASS_TO_HANDLERS | INPUT_SLOT;
	}

	return INPUT_PASS_TO_HANDLERS;
}