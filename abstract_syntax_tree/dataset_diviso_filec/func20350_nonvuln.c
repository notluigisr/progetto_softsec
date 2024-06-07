char *qemu_console_get_label(QemuConsole *con)
{
    if (con->console_type == GRAPHIC_CONSOLE) {
        if (con->device) {
            return g_strdup(object_get_typename(con->device));
        }
        return g_strdup("STR");
    } else {
        if (con->chr && con->chr->label) {
            return g_strdup(con->chr->label);
        }
        return g_strdup_printf("STR", con->index);
    }
}