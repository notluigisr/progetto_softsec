static void dio_cleanup(struct dio *dio)
{
	while (dio_pages_present(dio))
		page_cache_release(dio_get_page(dio));
}