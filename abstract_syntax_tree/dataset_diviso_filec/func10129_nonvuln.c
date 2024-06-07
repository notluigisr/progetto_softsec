static void automount_init(Unit *u) {
        Automount *a = AUTOMOUNT(u);

        assert(u);
        assert(u->load_state == UNIT_STUB);

        a->pipe_fd = -1;
        a->directory_mode = 0755;
        UNIT(a)->ignore_on_isolate = true;
}