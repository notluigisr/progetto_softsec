static void parse_next_body_multipart_init(struct message_parser_ctx *ctx)
{
	struct message_boundary *b;

	b = i_new(struct message_boundary, 1);
	b->part = ctx->part;
	b->boundary = ctx->last_boundary;
	ctx->last_boundary = NULL;
	b->len = strlen(b->boundary);

	b->next = ctx->boundaries;
	ctx->boundaries = b;
}