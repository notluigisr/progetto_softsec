void WavOutFile::fillInHeader(uint sampleRate, uint bits, uint channels)
{
    

    
    memcpy(&(header.riff.riff_char), riffStr, 4);
    
    header.riff.package_len = 0;
    
    memcpy(&(header.riff.wave), waveStr, 4);

    

    
    memcpy(&(header.format.fmt), fmtStr, 4);

    header.format.format_len = 0x10;
    header.format.fixed = 1;
    header.format.channel_number = (short)channels;
    header.format.sample_rate = (int)sampleRate;
    header.format.bits_per_sample = (short)bits;
    header.format.byte_per_sample = (short)(bits * channels / 8);
    header.format.byte_rate = header.format.byte_per_sample * (int)sampleRate;
    header.format.sample_rate = (int)sampleRate;

    
    memcpy(&(header.fact.fact_field), factStr, 4);
	header.fact.fact_len = 4;
	header.fact.fact_sample_len = 0;

    

    
    memcpy(&(header.data.data_field), dataStr, 4);
    
    header.data.data_len = 0;
}