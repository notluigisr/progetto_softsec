char *problem_data_get_content_or_NULL(problem_data_t *problem_data, const char *key)
{
    struct problem_item *item = problem_data_get_item_or_NULL(problem_data, key);
    if (!item)
        return NULL;
    return item->content;
}