void TDStretch::setParameters(int aSampleRate, int aSequenceMS, 
                              int aSeekWindowMS, int aOverlapMS)
{
    
    if (aSampleRate > 0)
    {
        if (aSampleRate > 192000) ST_THROW_RT_ERROR("STR");
        this->sampleRate = aSampleRate;
    }

    if (aOverlapMS > 0) this->overlapMs = aOverlapMS;

    if (aSequenceMS > 0)
    {
        this->sequenceMs = aSequenceMS;
        bAutoSeqSetting = false;
    } 
    else if (aSequenceMS == 0)
    {
        
        bAutoSeqSetting = true;
    }

    if (aSeekWindowMS > 0) 
    {
        this->seekWindowMs = aSeekWindowMS;
        bAutoSeekSetting = false;
    } 
    else if (aSeekWindowMS == 0) 
    {
        
        bAutoSeekSetting = true;
    }

    calcSeqParameters();

    calculateOverlapLength(overlapMs);

    
    setTempo(tempo);
}