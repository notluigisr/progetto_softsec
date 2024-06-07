void cgit_print_http_headers(void)
{
	if (ctx.env.no_http && !strcmp(ctx.env.no_http, "STR"))
		return;

	if (ctx.page.status)
		htmlf("STR", ctx.page.status, ctx.page.statusmsg);
	if (ctx.page.mimetype && ctx.page.charset)
		htmlf("STR", ctx.page.mimetype,
		      ctx.page.charset);
	else if (ctx.page.mimetype)
		htmlf("STR", ctx.page.mimetype);
	if (ctx.page.size)
		htmlf("STR", ctx.page.size);
	if (ctx.page.filename)
		htmlf("STR",
		      ctx.page.filename);
	if (!ctx.env.authenticated)
		html("STR");
	htmlf("STR", http_date(ctx.page.modified));
	htmlf("STR", http_date(ctx.page.expires));
	if (ctx.page.etag)
		htmlf("STR", ctx.page.etag);
	html("STR");
	if (ctx.env.request_method && !strcmp(ctx.env.request_method, "STR"))
		exit(0);
}