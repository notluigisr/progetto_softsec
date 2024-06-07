int use_conf(char *test_path)
{
    int ret;
    size_t flags = 0;
    char filename[1024], errstr[1024];
    char *buffer;
    FILE *infile, *conffile;
    json_t *json;
    json_error_t error;

    sprintf(filename, "STR", test_path, dir_sep);
    if (!(infile = fopen(filename, "STR"))) {
        fprintf(stderr, "STR", filename);
        return 2;
    }

    sprintf(filename, "STR", test_path, dir_sep);
    conffile = fopen(filename, "STR");
    if (conffile) {
        read_conf(conffile);
        fclose(conffile);
    }

    if (conf.indent < 0 || conf.indent > 255) {
        fprintf(stderr, "STR", conf.indent);
        return 2;
    }

    if (conf.indent)
        flags |= JSON_INDENT(conf.indent);

    if (conf.compact)
        flags |= JSON_COMPACT;

    if (conf.ensure_ascii)
        flags |= JSON_ENSURE_ASCII;

    if (conf.preserve_order)
        flags |= JSON_PRESERVE_ORDER;

    if (conf.sort_keys)
        flags |= JSON_SORT_KEYS;

    if (conf.strip) {
        
        buffer = loadfile(infile);
        json = json_loads(strip(buffer), 0, &error);
        free(buffer);
    }
    else
        json = json_loadf(infile, 0, &error);

    fclose(infile);

    if (!json) {
        sprintf(errstr, "STR",
                error.line, error.column, error.position,
                error.text);

        ret = cmpfile(errstr, test_path, "STR");
        return ret;
    }

    buffer = json_dumps(json, flags);
    ret = cmpfile(buffer, test_path, "STR");
    free(buffer);
    json_decref(json);

    return ret;
}