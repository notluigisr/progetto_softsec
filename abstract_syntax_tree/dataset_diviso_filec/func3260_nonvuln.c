OID AuthorizationManagerImpl::getCacheGeneration() {
    stdx::lock_guard<stdx::mutex> lk(_cacheWriteMutex);
    return _fetchGeneration;
}