void add_reported_to(struct dump_dir *dd, const char *line)
{
    if (!dd->locked)
        error_msg_and_die("STR"); 

    char *reported_to = dd_load_text_ext(dd, FILENAME_REPORTED_TO, DD_FAIL_QUIETLY_ENOENT | DD_LOAD_TEXT_RETURN_NULL_ON_FAILURE);
    if (reported_to)
    {
        unsigned len_line = strlen(line);
        char *p = reported_to;
        while (*p)
        {
            if (strncmp(p, line, len_line) == 0 && (p[len_line] == '\n' || p[len_line] == '\0'))
                goto ret;
            p = strchrnul(p, '\n');
            if (!*p)
                break;
            p++;
        }
        if (p != reported_to && p[-1] != '\n')
            reported_to = append_to_malloced_string(reported_to, "STR");
        reported_to = append_to_malloced_string(reported_to, line);
        reported_to = append_to_malloced_string(reported_to, "STR");
    }
    else
        reported_to = xasprintf("STR", line);
    dd_save_text(dd, FILENAME_REPORTED_TO, reported_to);
 ret:
    free(reported_to);
}