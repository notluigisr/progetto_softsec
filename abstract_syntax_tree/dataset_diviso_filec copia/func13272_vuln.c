rndr_quote(struct buf *ob, const struct buf *text, void *opaque)
{
	if (!text || !text->size)
		return 0;

	BUFPUTSL(ob, "STR");
	bufput(ob, text->data, text->size);
	BUFPUTSL(ob, "STR");

	return 1;
}