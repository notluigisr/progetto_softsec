static void exec_command_dump(ExecCommand *c, FILE *f, const char *prefix) {
        _cleanup_free_ char *cmd = NULL;
        const char *prefix2;

        assert(c);
        assert(f);

        prefix = strempty(prefix);
        prefix2 = strjoina(prefix, "STR");

        cmd = exec_command_line(c->argv);
        fprintf(f,
                "STR",
                prefix, cmd ? cmd : strerror(ENOMEM));

        exec_status_dump(&c->exec_status, f, prefix2);
}