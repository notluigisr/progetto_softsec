static int mov_write_stss_tag(AVIOContext *pb, MOVTrack *track, uint32_t flag)
{
    int64_t curpos, entryPos;
    int i, index = 0;
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0); 
    ffio_wfourcc(pb, flag == MOV_SYNC_SAMPLE ? "STR");
    avio_wb32(pb, 0); 
    entryPos = avio_tell(pb);
    avio_wb32(pb, track->entry); 
    for (i = 0; i < track->entry; i++) {
        if (track->cluster[i].flags & flag) {
            avio_wb32(pb, i + 1);
            index++;
        }
    }
    curpos = avio_tell(pb);
    avio_seek(pb, entryPos, SEEK_SET);
    avio_wb32(pb, index); 
    avio_seek(pb, curpos, SEEK_SET);
    return update_size(pb, pos);
}