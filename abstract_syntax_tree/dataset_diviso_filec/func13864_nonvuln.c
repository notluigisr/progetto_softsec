ldbm_config_pagedlookthroughlimit_get(void *arg)
{
    struct ldbminfo *li = (struct ldbminfo *)arg;

    return (void *)((uintptr_t)(li->li_pagedlookthroughlimit));
}