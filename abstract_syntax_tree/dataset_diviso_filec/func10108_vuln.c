cmsHPROFILE CMSEXPORT cmsCreateInkLimitingDeviceLinkTHR(cmsContext ContextID,
                                                     cmsColorSpaceSignature ColorSpace,
                                                     cmsFloat64Number Limit)
{
    cmsHPROFILE hICC;
    cmsPipeline* LUT;
    cmsStage* CLUT;
    int nChannels;

    if (ColorSpace != cmsSigCmykData) {
        cmsSignalError(ContextID, cmsERROR_COLORSPACE_CHECK, "STR");
        return NULL;
    }

    if (Limit < 0.0 || Limit > 400) {

        cmsSignalError(ContextID, cmsERROR_RANGE, "STR");
        if (Limit < 0) Limit = 0;
        if (Limit > 400) Limit = 400;

    }

    hICC = cmsCreateProfilePlaceholder(ContextID);
    if (!hICC)                          
        return NULL;

    cmsSetProfileVersion(hICC, 4.3);

    cmsSetDeviceClass(hICC,      cmsSigLinkClass);
    cmsSetColorSpace(hICC,       ColorSpace);
    cmsSetPCS(hICC,              ColorSpace);

    cmsSetHeaderRenderingIntent(hICC,  INTENT_PERCEPTUAL);


    
    LUT = cmsPipelineAlloc(ContextID, 4, 4);
    if (LUT == NULL) goto Error;


    nChannels = cmsChannelsOf(ColorSpace);

    CLUT = cmsStageAllocCLut16bit(ContextID, 17, nChannels, nChannels, NULL);
    if (CLUT == NULL) goto Error;

    if (!cmsStageSampleCLut16bit(CLUT, InkLimitingSampler, (void*) &Limit, 0)) goto Error;

    cmsPipelineInsertStage(LUT, cmsAT_BEGIN, _cmsStageAllocIdentityCurves(ContextID, nChannels));
    cmsPipelineInsertStage(LUT, cmsAT_END, CLUT);
    cmsPipelineInsertStage(LUT, cmsAT_END, _cmsStageAllocIdentityCurves(ContextID, nChannels));

    
    if (!SetTextTags(hICC, L"STR")) goto Error;

    if (!cmsWriteTag(hICC, cmsSigAToB0Tag, (void*) LUT))  goto Error;
    if (!SetSeqDescTag(hICC, "STR")) goto Error;

    
    cmsPipelineFree(LUT);

    
    return hICC;

Error:
    if (LUT != NULL)
        cmsPipelineFree(LUT);

    if (hICC != NULL)
        cmsCloseProfile(hICC);

    return NULL;
}