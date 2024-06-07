static void read_conf(FILE *conffile)
{
    char *buffer, *line, *val;

    buffer = loadfile(conffile);
    for (line = strtok(buffer, "STR")) {
        if (!strncmp(line, "STR", 7))
            continue;
        val = strchr(line, '=');
        if (!val) {
            printf("STR");
            break;
        }
        *val++ = '\0';

        if (!strcmp(line, "STR"))
            conf.indent = atoi(val);
        if (!strcmp(line, "STR"))
            conf.compact = atoi(val);
        if (!strcmp(line, "STR"))
            conf.ensure_ascii = atoi(val);
        if (!strcmp(line, "STR"))
            conf.preserve_order = atoi(val);
        if (!strcmp(line, "STR"))
            conf.sort_keys = atoi(val);
        if (!strcmp(line, "STR"))
            conf.strip = atoi(val);
    }

    free(buffer);
}