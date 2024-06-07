const char *RtmpProtocol::onSearchPacketTail(const char *data,size_t len){
    
    auto next_step_func(std::move(_next_step_func));
    
    auto ret = next_step_func(data, len);
    if (!_next_step_func) {
        
        next_step_func.swap(_next_step_func);
    }
    return ret;
}