static inline void open_auth_filter(const char *function)
{
	cgit_open_filter(ctx.cfg.auth_filter, function,
		ctx.env.http_cookie ? ctx.env.http_cookie : "",
		ctx.env.request_method ? ctx.env.request_method : "",
		ctx.env.query_string ? ctx.env.query_string : "",
		ctx.env.http_referer ? ctx.env.http_referer : "",
		ctx.env.path_info ? ctx.env.path_info : "",
		ctx.env.http_host ? ctx.env.http_host : "",
		ctx.env.https ? ctx.env.https : "",
		ctx.qry.repo ? ctx.qry.repo : "",
		ctx.qry.page ? ctx.qry.page : "",
		ctx.qry.url ? ctx.qry.url : "",
		cgit_loginurl());
}