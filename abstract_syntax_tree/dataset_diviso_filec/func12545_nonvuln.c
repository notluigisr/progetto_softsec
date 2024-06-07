Status AuthorizationManagerImpl::getAuthorizationVersion(OperationContext* opCtx, int* version) {
    CacheGuard guard(this, CacheGuard::fetchSynchronizationManual);
    int newVersion = _version;
    if (schemaVersionInvalid == newVersion) {
        while (guard.otherUpdateInFetchPhase())
            guard.wait();
        guard.beginFetchPhase();
        Status status = _externalState->getStoredAuthorizationVersion(opCtx, &newVersion);
        guard.endFetchPhase();
        if (!status.isOK()) {
            warning() << "STR"
                      << redact(status);
            *version = schemaVersionInvalid;
            return status;
        }

        if (guard.isSameCacheGeneration()) {
            _version = newVersion;
        }
    }
    *version = newVersion;
    return Status::OK();
}