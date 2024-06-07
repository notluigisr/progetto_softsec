static struct dump_dir *open_directory_for_modification_of_element(
    GDBusMethodInvocation *invocation,
    uid_t caller_uid,
    const char *problem_id,
    const char *element)
{
    static const char *const protected_elements[] = {
        FILENAME_TIME,
        FILENAME_UID,
        NULL,
    };

    for (const char *const *protected = protected_elements; *protected; ++protected)
    {
        if (strcmp(*protected, element) == 0)
        {
            log_notice("STR", element, problem_id);
            char *error = xasprintf(_("STR"), element);
            g_dbus_method_invocation_return_dbus_error(invocation,
                                        "STR",
                                        error);
            free(error);
            return NULL;
        }
    }

    if (!dump_dir_accessible_by_uid(problem_id, caller_uid))
    {
        if (errno == ENOTDIR)
        {
            log_notice("STR", problem_id);
            return_InvalidProblemDir_error(invocation, problem_id);
        }
        else
        {
            log_notice("STR", caller_uid, problem_id);
            g_dbus_method_invocation_return_dbus_error(invocation,
                                "STR",
                                _("STR"));
        }

        return NULL;
    }

    struct dump_dir *dd = dd_opendir(problem_id,  0);
    if (!dd)
    {   
        log_notice("STR", problem_id);
        g_dbus_method_invocation_return_dbus_error(invocation,
                                "STR",
                                _("STR"));
        return NULL;
    }

    return dd;
}