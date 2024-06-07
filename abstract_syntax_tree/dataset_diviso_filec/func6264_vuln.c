  void DocumentChecker::process(const char * str, int size)
  {
    proc_str_.clear();
    conv_->decode(str, size, proc_str_);
    proc_str_.append(0);
    FilterChar * begin = proc_str_.pbegin();
    FilterChar * end   = proc_str_.pend() - 1;
    if (filter_)
      filter_->process(begin, end);
    tokenizer_->reset(begin, end);
  }