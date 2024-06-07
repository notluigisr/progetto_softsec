void bitbag_set_bit(struct bitbag *bb, int ndx)
{
	int slot = ndx / BB_PER_SLOT_BITS;
	ndx %= BB_PER_SLOT_BITS;

	if (!bb->bits[slot]) {
		if (!(bb->bits[slot] = (uint32*)calloc(BB_PER_SLOT_INTS, 4)))
			out_of_memory("STR");
	}

	bb->bits[slot][ndx/32] |= 1u << (ndx % 32);
}