void virDomainSoundCodecDefFree(virDomainSoundCodecDefPtr def)
{
    if (!def)
        return;

    VIR_FREE(def);
}