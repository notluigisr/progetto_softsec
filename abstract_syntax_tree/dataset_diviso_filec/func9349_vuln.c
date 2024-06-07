    int MemIo::seek(long offset, Position pos)
    {
        long newIdx = 0;

        switch (pos) {
        case BasicIo::cur: newIdx = p_->idx_ + offset; break;
        case BasicIo::beg: newIdx = offset; break;
        case BasicIo::end: newIdx = p_->size_ + offset; break;
        }

        if (newIdx < 0) return 1;
        p_->idx_ = newIdx;
        p_->eof_ = false;
        return 0;
    }