    int FileIo::Impl::switchMode(OpMode opMode)
    {
        if (fp_ == nullptr)
            return 1;
        if (opMode_ == opMode)
            return 0;
        OpMode oldOpMode = opMode_;
        opMode_ = opMode;

        bool reopen = true;
        switch (opMode) {
            case opRead:
                
                
                if (openMode_[0] == 'r' || openMode_[1] == '+')
                    reopen = false;
                break;
            case opWrite:
                
                if (openMode_[0] != 'r' || openMode_[1] == '+')
                    reopen = false;
                break;
            case opSeek:
                reopen = false;
                break;
        }

        if (!reopen) {
            
            
            if (oldOpMode == opSeek)
                return 0;

            
            std::fseek(fp_, 0, SEEK_CUR);
            return 0;
        }

        
        long offset = std::ftell(fp_);
        if (offset == -1)
            return -1;
        
        std::fclose(fp_);
        openMode_ = "STR";
        opMode_ = opSeek;
#ifdef EXV_UNICODE_PATH
        if (wpMode_ == wpUnicode) {
            fp_ = ::_wfopen(wpath_.c_str(), s2ws(openMode_).c_str());
        } else
#endif
        {
            fp_ = std::fopen(path_.c_str(), openMode_.c_str());
        }
        if (fp_ == nullptr)
            return 1;
        return std::fseek(fp_, offset, SEEK_SET);
    }  