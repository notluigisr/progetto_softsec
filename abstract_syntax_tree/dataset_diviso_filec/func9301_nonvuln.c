void VP8ComponentDecoder::initialize( Sirikata::DecoderReader *input,
                                      const std::vector<ThreadHandoff>& thread_handoff)
{
    str_in = input;
    mux_reader_.init(input);
    thread_handoff_ = thread_handoff;
}