ldbm_config_backend_implement_get(void *arg)
{
    struct ldbminfo *li = (struct ldbminfo *)arg;

    return (void *)slapi_ch_strdup(li->li_backend_implement);
}