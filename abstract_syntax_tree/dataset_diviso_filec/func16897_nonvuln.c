void ldbFlushLog(list *log) {
    listNode *ln;

    while((ln = listFirst(log)) != NULL)
        listDelNode(log,ln);
}