minimask_init(struct minimask *mask, const struct flow_wildcards *wc)
{
    miniflow_init(&mask->masks, &wc->masks);
}