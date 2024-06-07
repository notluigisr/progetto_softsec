std::vector<AuthorizationManager::CachedUserInfo> AuthorizationManagerImpl::getUserCacheInfo()
    const {
    auto cacheData = _userCache.getCacheInfo();
    std::vector<AuthorizationManager::CachedUserInfo> ret;
    ret.reserve(cacheData.size());
    std::transform(
        cacheData.begin(), cacheData.end(), std::back_inserter(ret), [](const auto& info) {
            return AuthorizationManager::CachedUserInfo{info.key, info.active};
        });

    return ret;
}