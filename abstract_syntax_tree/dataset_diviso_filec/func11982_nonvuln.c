cmsBool IsTypeSupported(cmsTagDescriptor* TagDescriptor, cmsTagTypeSignature Type)
{
    cmsUInt32Number i, nMaxTypes;

    nMaxTypes = TagDescriptor->nSupportedTypes;
    if (nMaxTypes >= MAX_TYPES_IN_LCMS_PLUGIN)
        nMaxTypes = MAX_TYPES_IN_LCMS_PLUGIN;

    for (i=0; i < nMaxTypes; i++) {
        if (Type == TagDescriptor ->SupportedTypes[i]) return TRUE;
    }

    return FALSE;
}