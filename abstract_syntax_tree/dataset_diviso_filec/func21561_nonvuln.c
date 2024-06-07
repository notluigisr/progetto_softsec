TRIO_PUBLIC void trio_locale_set_grouping TRIO_ARGS1((grouping), char* grouping)
{
#if defined(USE_LOCALE)
	if (NULL == internalLocaleValues)
	{
		TrioSetLocale();
	}
#endif
	trio_copy_max(internalGrouping, sizeof(internalGrouping), grouping);
}