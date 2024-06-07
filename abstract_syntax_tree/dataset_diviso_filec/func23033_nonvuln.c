void FIFOSampleBuffer::ensureCapacity(uint capacityRequirement)
{
    SAMPLETYPE *tempUnaligned, *temp;

    if (capacityRequirement > getCapacity()) 
    {
        
        sizeInBytes = (capacityRequirement * channels * sizeof(SAMPLETYPE) + 4095) & (uint)-4096;
        assert(sizeInBytes % 2 == 0);
        tempUnaligned = new SAMPLETYPE[sizeInBytes / sizeof(SAMPLETYPE) + 16 / sizeof(SAMPLETYPE)];
        if (tempUnaligned == NULL)
        {
            ST_THROW_RT_ERROR("STR");
        }
        
        temp = (SAMPLETYPE *)SOUNDTOUCH_ALIGN_POINTER_16(tempUnaligned);
        if (samplesInBuffer)
        {
            memcpy(temp, ptrBegin(), samplesInBuffer * channels * sizeof(SAMPLETYPE));
        }
        delete[] bufferUnaligned;
        buffer = temp;
        bufferUnaligned = tempUnaligned;
        bufferPos = 0;
    } 
    else 
    {
        
        rewind();
    }
}