static void exec_command_done(ExecCommand *c) {
        assert(c);

        c->path = mfree(c->path);
        c->argv = strv_free(c->argv);
}