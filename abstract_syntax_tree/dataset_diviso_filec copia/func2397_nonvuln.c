    CacheGuard(AuthorizationManager* authzManager,
               const FetchSynchronization sync = fetchSynchronizationAutomatic)
        : _isThisGuardInFetchPhase(false),
          _authzManager(authzManager),
          _lock(authzManager->_cacheMutex) {
        if (fetchSynchronizationAutomatic == sync) {
            synchronizeWithFetchPhase();
        }
    }