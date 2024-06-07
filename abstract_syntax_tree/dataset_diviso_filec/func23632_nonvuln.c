void *vrend_renderer_resource_get_priv(uint32_t res_handle)
{
    struct vrend_resource *res = vrend_resource_lookup(res_handle, 0);
    if (!res)
       return NULL;

    return res->priv;
}