ASC_getAPTitles(T_ASC_Parameters * params,
    char* callingAPTitle,
    size_t callingAPTitleSize,
    char* calledAPTitle,
    size_t calledAPTitleSize,
    char* respondingAPTitle,
    size_t respondingAPTitleSize)
{
    if (callingAPTitle)
        OFStandard::strlcpy(callingAPTitle, params->DULparams.callingAPTitle, callingAPTitleSize);
    if (calledAPTitle)
        OFStandard::strlcpy(calledAPTitle, params->DULparams.calledAPTitle, calledAPTitleSize);
    if (respondingAPTitle)
        OFStandard::strlcpy(respondingAPTitle, params->DULparams.respondingAPTitle, respondingAPTitleSize);

    return EC_Normal;
}