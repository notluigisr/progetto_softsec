static int read_link(link_ctx *ctx)
{
    if (skip_ws(ctx) && read_chr(ctx, '<')) {
        size_t end;
        if (find_chr(ctx, '>', &end)) {
            ctx->link = mk_str(ctx, end);
            ctx->i = end + 1;
            return 1;
        }
    }
    return 0;
}