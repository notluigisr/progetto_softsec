static int displaytext_get_tag_len(const char *tagstr)
{
    char *colon = strchr(tagstr, ':');

    return (colon == NULL) ? -1 : colon - tagstr;
}