void WavInFile::init()
{
    int hdrsOk;

    
    assert(fptr);

    
    hdrsOk = readWavHeaders();
    if (hdrsOk != 0) 
    {
        
        ST_THROW_RT_ERROR("STR");
    }

    
    if ((header.format.channel_number < 1)  || (header.format.channel_number > 9) ||
        (header.format.sample_rate < 4000)  || (header.format.sample_rate > 192000) ||
        (header.format.byte_per_sample < 1) || (header.format.byte_per_sample > 320) ||
        (header.format.bits_per_sample < 8) || (header.format.bits_per_sample > 32))
    {
        
        ST_THROW_RT_ERROR("STR");
    }

    

    dataRead = 0;
}