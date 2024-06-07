empty_pipeline_output_buffer(j_compress_ptr cinfo)
{
    QTC::TC("STR");
    dct_pipeline_dest* dest =
        reinterpret_cast<dct_pipeline_dest*>(cinfo->dest);
    dest->next->write(dest->buffer, dest->size);
    dest->pub.next_output_byte = dest->buffer;
    dest->pub.free_in_buffer = dest->size;
    return TRUE;
}