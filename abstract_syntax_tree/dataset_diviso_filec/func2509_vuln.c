void TDStretch::setChannels(int numChannels)
{
    assert(numChannels > 0);
    if (channels == numChannels) return;


    channels = numChannels;
    inputBuffer.setChannels(channels);
    outputBuffer.setChannels(channels);

    
    overlapLength=0;
    setParameters(sampleRate);
}