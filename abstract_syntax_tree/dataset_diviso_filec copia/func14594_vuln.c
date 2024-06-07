cmsPipeline* _cmsReadFloatOutputTag(cmsHPROFILE hProfile, cmsTagSignature tagFloat)
{
    cmsContext ContextID       = cmsGetProfileContextID(hProfile);
    cmsPipeline* Lut           = cmsPipelineDup((cmsPipeline*) cmsReadTag(hProfile, tagFloat));
    cmsColorSpaceSignature PCS = cmsGetPCS(hProfile);
    cmsColorSpaceSignature dataSpace = cmsGetColorSpace(hProfile);
    
    if (Lut == NULL) return NULL;
    
    
    
    if ( PCS == cmsSigLabData)
    {
        cmsPipelineInsertStage(Lut, cmsAT_BEGIN, _cmsStageNormalizeToLabFloat(ContextID));
    }
    else
        if (PCS == cmsSigXYZData)
        {
            cmsPipelineInsertStage(Lut, cmsAT_BEGIN, _cmsStageNormalizeToXyzFloat(ContextID));
        }
    
    
    if ( dataSpace == cmsSigLabData)
    {
        cmsPipelineInsertStage(Lut, cmsAT_END, _cmsStageNormalizeFromLabFloat(ContextID));
    }
    else if ( dataSpace == cmsSigXYZData)
    {
        cmsPipelineInsertStage(Lut, cmsAT_END, _cmsStageNormalizeFromXyzFloat(ContextID));
    }
    
    return Lut;
}