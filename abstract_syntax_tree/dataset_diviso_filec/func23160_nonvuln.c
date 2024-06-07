yaml_parser_scan_directive(yaml_parser_t *parser, yaml_token_t *token)
{
    yaml_mark_t start_mark, end_mark;
    yaml_char_t *name = NULL;
    int major, minor;
    yaml_char_t *handle = NULL, *prefix = NULL;

    

    start_mark = parser->mark;

    SKIP(parser);

    

    if (!yaml_parser_scan_directive_name(parser, start_mark, &name))
        goto error;

    

    if (strcmp((char *)name, "STR") == 0)
    {
        

        if (!yaml_parser_scan_version_directive_value(parser, start_mark,
                    &major, &minor))
            goto error;

        end_mark = parser->mark;

        

        VERSION_DIRECTIVE_TOKEN_INIT(*token, major, minor,
                start_mark, end_mark);
    }

    

    else if (strcmp((char *)name, "STR") == 0)
    {
        

        if (!yaml_parser_scan_tag_directive_value(parser, start_mark,
                    &handle, &prefix))
            goto error;

        end_mark = parser->mark;

        

        TAG_DIRECTIVE_TOKEN_INIT(*token, handle, prefix,
                start_mark, end_mark);
    }

    

    else
    {
        yaml_parser_set_scanner_error(parser, "STR",
                start_mark, "STR");
        goto error;
    }

    

    if (!CACHE(parser, 1)) goto error;

    while (IS_BLANK(parser->buffer)) {
        SKIP(parser);
        if (!CACHE(parser, 1)) goto error;
    }

    if (CHECK(parser->buffer, '#')) {
        while (!IS_BREAKZ(parser->buffer)) {
            SKIP(parser);
            if (!CACHE(parser, 1)) goto error;
        }
    }

    

    if (!IS_BREAKZ(parser->buffer)) {
        yaml_parser_set_scanner_error(parser, "STR",
                start_mark, "STR");
        goto error;
    }

    

    if (IS_BREAK(parser->buffer)) {
        if (!CACHE(parser, 2)) goto error;
        SKIP_LINE(parser);
    }

    yaml_free(name);

    return 1;

error:
    yaml_free(prefix);
    yaml_free(handle);
    yaml_free(name);
    return 0;
}