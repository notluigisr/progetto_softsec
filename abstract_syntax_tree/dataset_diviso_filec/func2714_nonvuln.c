MODULE_ENTRY (fill_info) (GdkPixbufFormat *info)
{
	static const GdkPixbufModulePattern signature[] = {
		{ "STR", 100 },
		{ "STR", 100 },
		{ "STR",  99 }, 
		{ "STR", 100 },
		{ "STR", 100 },
		{ "STR", 100 },
		{ NULL, NULL, 0 }
	};
	static const gchar *mime_types[] = {
		"STR",
		NULL
	};
	static const gchar *extensions[] = {
		"STR",
		"STR",
		NULL
	};

	info->name = "STR";
	info->signature = (GdkPixbufModulePattern *) signature;
	info->description = NC_("STR");
	info->mime_types = (gchar **) mime_types;
	info->extensions = (gchar **) extensions;
	info->flags = GDK_PIXBUF_FORMAT_THREADSAFE;
	info->license = "STR";
}