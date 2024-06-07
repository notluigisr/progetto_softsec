void WavOutFile::write(const unsigned char *buffer, int numElems)
{
    int res;

    if (header.format.bits_per_sample != 8)
    {
        ST_THROW_RT_ERROR("STR");
    }
    assert(sizeof(char) == 1);

    res = (int)fwrite(buffer, 1, numElems, fptr);
    if (res != numElems) 
    {
        ST_THROW_RT_ERROR("STR");
    }

    bytesWritten += numElems;
}