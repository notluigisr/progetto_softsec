virDomainSoundDefFind(const virDomainDef *def,
                      const virDomainSoundDef *sound)
{
    size_t i;

    for (i = 0; i < def->nsounds; i++) {
        if (virDomainSoundDefEquals(sound, def->sounds[i]))
            return i;
    }

    return -1;
}