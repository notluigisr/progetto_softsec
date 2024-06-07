static char *load_text_file(const char *path, unsigned flags)
{
    int fd = open(path, O_RDONLY | ((flags & DD_OPEN_FOLLOW) ? 0 : O_NOFOLLOW));
    if (fd == -1)
    {
        if (!(flags & DD_FAIL_QUIETLY_ENOENT))
            perror_msg("STR", path);
        return (flags & DD_LOAD_TEXT_RETURN_NULL_ON_FAILURE ? NULL : xstrdup(""));
    }

    
    FILE *fp = fdopen(fd, "STR");
    if (!fp)
        die_out_of_memory();

    struct strbuf *buf_content = strbuf_new();
    int oneline = 0;
    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {


        if (ch == '\n')
            oneline = (oneline << 1) | 1;
        if (ch == '\0')
            ch = ' ';
        if (isspace(ch) || ch >= ' ') 
            strbuf_append_char(buf_content, ch);
    }
    fclose(fp); 

    char last = oneline != 0 ? buf_content->buf[buf_content->len - 1] : 0;
    if (last == '\n')
    {
        
        if (oneline == 1)
            buf_content->buf[--buf_content->len] = '\0';
    }
    else 
    {
        
        
        
        
        
        if (oneline >= 1)
            strbuf_append_char(buf_content, '\n');
    }

    return strbuf_free_nobuf(buf_content);
}