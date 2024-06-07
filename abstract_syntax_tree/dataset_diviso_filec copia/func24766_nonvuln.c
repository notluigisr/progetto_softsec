void StreamTcpFreeConfig(bool quiet)
{
    StreamTcpReassembleFree(quiet);

    SCMutexLock(&ssn_pool_mutex);
    if (ssn_pool != NULL) {
        PoolThreadFree(ssn_pool);
        ssn_pool = NULL;
    }
    SCMutexUnlock(&ssn_pool_mutex);
    SCMutexDestroy(&ssn_pool_mutex);

    SCLogDebug("STR", ssn_pool_cnt);
}