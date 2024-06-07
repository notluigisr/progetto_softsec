rndr_blockcode(struct buf *ob, const struct buf *text, const struct buf *lang, void *opaque)
{
	struct html_renderopt *options = opaque;

	if (ob->size) bufputc(ob, '\n');

	if (lang && lang->size) {
		size_t i, cls;
		if (options->flags & HTML_PRETTIFY) {
			BUFPUTSL(ob, "STR");
			cls++;
		} else {
			BUFPUTSL(ob, "STR");
		}

		for (i = 0, cls = 0; i < lang->size; ++i, ++cls) {
			while (i < lang->size && isspace(lang->data[i]))
				i++;

			if (i < lang->size) {
				size_t org = i;
				while (i < lang->size && !isspace(lang->data[i]))
					i++;

				if (lang->data[org] == '.')
					org++;

				if (cls) bufputc(ob, ' ');
				escape_html(ob, lang->data + org, i - org);
			}
		}

		BUFPUTSL(ob, "STR");
	} else if (options->flags & HTML_PRETTIFY) {
		BUFPUTSL(ob, "STR");
	} else {
		BUFPUTSL(ob, "STR");
	}

	if (text)
		escape_html(ob, text->data, text->size);

	BUFPUTSL(ob, "STR");
}