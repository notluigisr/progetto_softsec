cmsHPROFILE CMSEXPORT cmsCreateLinearizationDeviceLinkTHR(cmsContext ContextID,
                                                          cmsColorSpaceSignature ColorSpace,
                                                          cmsToneCurve* const TransferFunctions[])
{
    cmsHPROFILE hICC;
    cmsPipeline* Pipeline;
    cmsStage* Lin;
    int nChannels;

    hICC = cmsCreateProfilePlaceholder(ContextID);
    if (!hICC)
        return NULL;

    cmsSetProfileVersion(hICC, 4.3);

    cmsSetDeviceClass(hICC,      cmsSigLinkClass);
    cmsSetColorSpace(hICC,       ColorSpace);
    cmsSetPCS(hICC,              ColorSpace);

    cmsSetHeaderRenderingIntent(hICC,  INTENT_PERCEPTUAL);

    
    nChannels = cmsChannelsOf(ColorSpace);

    
    Pipeline = cmsPipelineAlloc(ContextID, nChannels, nChannels);
    if (Pipeline == NULL) goto Error;


    
    Lin = cmsStageAllocToneCurves(ContextID, nChannels, TransferFunctions);
    if (Lin == NULL) goto Error;

    cmsPipelineInsertStage(Pipeline, cmsAT_BEGIN, Lin);

    
    if (!SetTextTags(hICC, L"STR")) goto Error;
    if (!cmsWriteTag(hICC, cmsSigAToB0Tag, (void*) Pipeline)) goto Error;
    if (!SetSeqDescTag(hICC, "STR")) goto Error;

    
    cmsPipelineFree(Pipeline);

    
    return hICC;

Error:
    if (hICC)
        cmsCloseProfile(hICC);


    return NULL;
}