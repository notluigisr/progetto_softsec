void SSL::SendWriteBuffered()
{
    output_buffer* out = buffers_.TakeOutput();

    if (out) {
        mySTL::auto_ptr<output_buffer> tmp(out);
        Send(out->get_buffer(), out->get_size());
    }
}