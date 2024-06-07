void show_opcodes(u8 *rip, const char *loglvl)
{



	u8 opcodes[OPCODE_BUFSIZE];

	if (probe_kernel_read(opcodes, rip - PROLOGUE_SIZE, OPCODE_BUFSIZE)) {
		printk("STR", loglvl);
	} else {
		printk("STR"
		       __stringify(EPILOGUE_SIZE) "STR", loglvl, opcodes,
		       opcodes[PROLOGUE_SIZE], opcodes + PROLOGUE_SIZE + 1);
	}
}