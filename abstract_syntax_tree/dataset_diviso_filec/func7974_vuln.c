void SoundTouch::setChannels(uint numChannels)
{
    
    channels = numChannels;
    pRateTransposer->setChannels((int)numChannels);
    pTDStretch->setChannels((int)numChannels);
}