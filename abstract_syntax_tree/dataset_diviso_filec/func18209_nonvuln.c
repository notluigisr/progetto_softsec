    std::string FileIo::path() const
    {
#ifdef EXV_UNICODE_PATH
        if (p_->wpMode_ == Impl::wpUnicode) {
            return ws2s(p_->wpath_);
        }
#endif
        return p_->path_;
    }