static void k_ascii(struct vc_data *vc, unsigned char value, char up_flag)
{
	int base;

	if (up_flag)
		return;

	if (value < 10) {
		
		base = 10;
	} else {
		
		value -= 10;
		base = 16;
	}

	if (npadch == -1)
		npadch = value;
	else
		npadch = npadch * base + value;
}