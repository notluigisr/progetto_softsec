cmsStage* _cmsStageAllocLabV4ToV2(cmsContext ContextID)
{
    static const cmsFloat64Number V4ToV2[] = { 65280.0/65535.0, 0, 0,
                                     0, 65280.0/65535.0, 0,
                                     0, 0, 65280.0/65535.0
                                     };

     cmsStage *mpe = cmsStageAllocMatrix(ContextID, 3, 3, V4ToV2, NULL);

    if (mpe == NULL) return mpe;
    mpe ->Implements = cmsSigLabV4toV2;
    return mpe;
}