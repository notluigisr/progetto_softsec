format_single(struct cmdq_item *item, const char *fmt, struct client *c,
    struct session *s, struct winlink *wl, struct window_pane *wp)
{
	struct format_tree	*ft;
	char			*expanded;

	if (item != NULL)
		ft = format_create(item->client, item, FORMAT_NONE, 0);
	else
		ft = format_create(NULL, item, FORMAT_NONE, 0);
	format_defaults(ft, c, s, wl, wp);

	expanded = format_expand(ft, fmt);
	format_free(ft);
	return (expanded);
}