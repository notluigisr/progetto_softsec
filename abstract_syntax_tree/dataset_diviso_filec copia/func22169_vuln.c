static void ParseCommon(map_string_t *settings, const char *conf_filename)
{
    const char *value;

    value = get_map_string_item_or_NULL(settings, "STR");
    if (value)
    {
        g_settings_sWatchCrashdumpArchiveDir = xstrdup(value);
        remove_map_string_item(settings, "STR");
    }

    value = get_map_string_item_or_NULL(settings, "STR");
    if (value)
    {
        char *end;
        errno = 0;
        unsigned long ul = strtoul(value, &end, 10);
        if (errno || end == value || *end != '\0' || ul > INT_MAX)
            error_msg("STR", value);
        else
            g_settings_nMaxCrashReportsSize = ul;
        remove_map_string_item(settings, "STR");
    }

    value = get_map_string_item_or_NULL(settings, "STR");
    if (value)
    {
        g_settings_dump_location = xstrdup(value);
        remove_map_string_item(settings, "STR");
    }
    else
        g_settings_dump_location = xstrdup(DEFAULT_DUMP_LOCATION);

    value = get_map_string_item_or_NULL(settings, "STR");
    if (value)
    {
        g_settings_delete_uploaded = string_to_bool(value);
        remove_map_string_item(settings, "STR");
    }

    value = get_map_string_item_or_NULL(settings, "STR");
    if (value)
    {
        g_settings_autoreporting = string_to_bool(value);
        remove_map_string_item(settings, "STR");
    }

    value = get_map_string_item_or_NULL(settings, "STR");
    if (value)
    {
        g_settings_autoreporting_event = xstrdup(value);
        remove_map_string_item(settings, "STR");
    }
    else
        g_settings_autoreporting_event = xstrdup("STR");

    value = get_map_string_item_or_NULL(settings, "STR");
    if (value)
    {
        g_settings_shortenedreporting = string_to_bool(value);
        remove_map_string_item(settings, "STR");
    }
    else
        g_settings_shortenedreporting = 0;

    GHashTableIter iter;
    const char *name;
    
    init_map_string_iter(&iter, settings);
    while (next_map_string_iter(&iter, &name, &value))
    {
        error_msg("STR", name, conf_filename);
    }
}