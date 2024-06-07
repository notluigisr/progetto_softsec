    FileIo::FileIo(const std::string& path)
        : p_(new Impl(path))
    {
    }