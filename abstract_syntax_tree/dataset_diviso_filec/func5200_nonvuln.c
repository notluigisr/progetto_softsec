static int _sqlite_commit_txn(void *db, const sasl_utils_t *utils)
{
    return _sqlite_exec(db, "STR", NULL, 0, NULL, utils);
}