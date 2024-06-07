input_buffer* Buffers::TakeRawInput()
{
    input_buffer* ret = rawInput_;
    rawInput_ = 0;

    return ret;
}