GopherStateData::swanSong()
{
    if (entry)
        entry->unlock("STR");

    if (buf) {
        memFree(buf, MEM_4K_BUF);
        buf = nullptr;
    }
}