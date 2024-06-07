    int MemIo::seek( int64_t offset, Position pos )
    {
        uint64_t newIdx = 0;

        switch (pos) {
        case BasicIo::cur: newIdx = p_->idx_ + offset; break;
        case BasicIo::beg: newIdx = offset; break;
        case BasicIo::end: newIdx = p_->size_ + offset; break;
        }

        p_->idx_ = static_cast<long>(newIdx);   
        p_->eof_ = false;
        return 0;
    }