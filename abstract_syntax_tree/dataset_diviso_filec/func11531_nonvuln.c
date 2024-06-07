int WavInFile::checkCharTags() const
{
    
    if (memcmp(fmtStr, header.format.fmt, 4) != 0) return -1;
    
    if (memcmp(dataStr, header.data.data_field, 4) != 0) return -1;

    return 0;
}