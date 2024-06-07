static unsigned char asn1_header_decode(struct asn1_ctx *ctx,
					unsigned char **eoc,
					unsigned int *cls,
					unsigned int *con,
					unsigned int *tag)
{
	unsigned int def, len;

	if (!asn1_id_decode(ctx, cls, con, tag))
		return 0;

	def = len = 0;
	if (!asn1_length_decode(ctx, &def, &len))
		return 0;

	if (def)
		*eoc = ctx->pointer + len;
	else
		*eoc = NULL;
	return 1;
}