JpegSetDstManager(j_compress_ptr cinfo)
{
    jpegDstManager.init_destination = JpegInitDestination;
    jpegDstManager.empty_output_buffer = JpegEmptyOutputBuffer;
    jpegDstManager.term_destination = JpegTermDestination;
    cinfo->dest = &jpegDstManager;
}