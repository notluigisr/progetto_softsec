    int RemoteIo::seek(long offset, Position pos)
    {
        assert(p_->isMalloced_);
        long newIdx = 0;

        switch (pos) {
            case BasicIo::cur: newIdx = p_->idx_ + offset; break;
            case BasicIo::beg: newIdx = offset; break;
            case BasicIo::end: newIdx = p_->size_ + offset; break;
        }

        
        
        p_->idx_ = newIdx;
        p_->eof_ = newIdx > (long) p_->size_;
        if ( p_->idx_ > (long) p_->size_ ) p_->idx_= (long) p_->size_;
        return 0;
    }