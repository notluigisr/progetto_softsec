void killRDBChild(void) {
    kill(server.rdb_child_pid,SIGUSR1);
    rdbRemoveTempFile(server.rdb_child_pid, 0);
    closeChildInfoPipe();
    updateDictResizePolicy();
}