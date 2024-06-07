static int opclflush(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	int offset = 0;
	int mod_byte = 0;

	if (op->operands[0].type & OT_MEMORY) {
		data[l++] = 0x0f;
		data[l++] = 0xae;
		offset = op->operands[0].offset * op->operands[0].offset_sign;
		if (offset) {
			if (offset < ST8_MIN || offset > ST8_MAX) {
				mod_byte = 2;
			} else {
				mod_byte = 1;
			}
		}
		data[l++] = (mod_byte << 6) | (7 << 3) | op->operands[0].regs[0];
		if (mod_byte) {
			data[l++] = offset;
			if (mod_byte == 2) {
				data[l++] = offset >> 8;
				data[l++] = offset >> 16;
				data[l++] = offset >> 24;
			}
		}
	}
	return l;
}