static long i8042_panic_blink(int state)
{
	long delay = 0;
	char led;

	led = (state) ? 0x01 | 0x04 : 0;
	while (i8042_read_status() & I8042_STR_IBF)
		DELAY;
	dbg("STR", 0xed);
	i8042_suppress_kbd_ack = 2;
	i8042_write_data(0xed); 
	DELAY;
	while (i8042_read_status() & I8042_STR_IBF)
		DELAY;
	DELAY;
	dbg("STR", led);
	i8042_write_data(led);
	DELAY;
	return delay;
}