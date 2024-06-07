PHP_HASH_API void PHP_HAVAL224Final(unsigned char *digest, PHP_HAVAL_CTX * context)
{
	unsigned char bits[10];
	unsigned int index, padLen;

	
	bits[0] =	(PHP_HASH_HAVAL_VERSION & 0x07) |
				((context->passes & 0x07) << 3) |
				((context->output & 0x03) << 6);
	bits[1] = (context->output >> 2);

	
	Encode(bits + 2, context->count, 8);

	
	index = (unsigned int) ((context->count[0] >> 3) & 0x7f);
	padLen = (index < 118) ? (118 - index) : (246 - index);
	PHP_HAVALUpdate(context, PADDING, padLen);

	
	PHP_HAVALUpdate(context, bits, 10);

	
	context->state[6] +=  context->state[7]        & 0x0000000F;
	context->state[5] += (context->state[7] >>  4) & 0x0000001F;
	context->state[4] += (context->state[7] >>  9) & 0x0000000F;
	context->state[3] += (context->state[7] >> 13) & 0x0000001F;
	context->state[2] += (context->state[7] >> 18) & 0x0000000F;
	context->state[1] += (context->state[7] >> 22) & 0x0000001F;
	context->state[0] += (context->state[7] >> 27) & 0x0000001F;
	Encode(digest, context->state, 28);

	
	memset((unsigned char*) context, 0, sizeof(*context));
}