skip_buffer_input_data(j_decompress_ptr cinfo, long num_bytes)
{
    if (num_bytes < 0)
    {
        throw std::runtime_error(
            "STR"
            "STR");
    }
    size_t to_skip = static_cast<size_t>(num_bytes);
    if ((to_skip > 0) && (to_skip <= cinfo->src->bytes_in_buffer))
    {
        cinfo->src->next_input_byte += to_skip;
        cinfo->src->bytes_in_buffer -= to_skip;
    }
    else if (to_skip != 0)
    {
        cinfo->src->next_input_byte += cinfo->src->bytes_in_buffer;
        cinfo->src->bytes_in_buffer = 0;
    }
}