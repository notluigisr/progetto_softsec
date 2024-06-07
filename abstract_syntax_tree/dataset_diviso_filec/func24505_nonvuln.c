    std::vector<UserName> getUserNames() {
        stdx::lock_guard<stdx::mutex> lk(_mutex);
        return _userNames;
    }