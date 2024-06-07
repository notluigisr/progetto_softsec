int qemu_console_get_index(QemuConsole *con)
{
    if (con == NULL) {
        con = active_console;
    }
    return con ? con->index : -1;
}