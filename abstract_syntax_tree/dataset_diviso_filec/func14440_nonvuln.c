static int automount_stop(Unit *u) {
        Automount *a = AUTOMOUNT(u);

        assert(a);
        assert(a->state == AUTOMOUNT_WAITING || a->state == AUTOMOUNT_RUNNING);

        automount_enter_dead(a, AUTOMOUNT_SUCCESS);
        return 1;
}