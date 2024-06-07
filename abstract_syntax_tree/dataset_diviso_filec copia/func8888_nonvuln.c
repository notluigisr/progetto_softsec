static int mov_write_vmhd_tag(AVIOContext *pb)
{
    avio_wb32(pb, 0x14); 
    ffio_wfourcc(pb, "STR");
    avio_wb32(pb, 0x01); 
    avio_wb64(pb, 0); 
    return 0x14;
}