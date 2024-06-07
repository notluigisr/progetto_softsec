cmsPipeline* BuildRGBInputMatrixShaper(cmsHPROFILE hProfile)
{
    cmsPipeline* Lut;
    cmsMAT3 Mat;
    cmsToneCurve *Shapes[3];
    cmsContext ContextID = cmsGetProfileContextID(hProfile);
    int i, j;

    if (!ReadICCMatrixRGB2XYZ(&Mat, hProfile)) return NULL;

    
    
    

    for (i=0; i < 3; i++)
        for (j=0; j < 3; j++)
            Mat.v[i].n[j] *= InpAdj;


    Shapes[0] = (cmsToneCurve *) cmsReadTag(hProfile, cmsSigRedTRCTag);
    Shapes[1] = (cmsToneCurve *) cmsReadTag(hProfile, cmsSigGreenTRCTag);
    Shapes[2] = (cmsToneCurve *) cmsReadTag(hProfile, cmsSigBlueTRCTag);

    if (!Shapes[0] || !Shapes[1] || !Shapes[2])
        return NULL;

    Lut = cmsPipelineAlloc(ContextID, 3, 3);
    if (Lut != NULL) {
     
        cmsPipelineInsertStage(Lut, cmsAT_END, cmsStageAllocToneCurves(ContextID, 3, Shapes));
        cmsPipelineInsertStage(Lut, cmsAT_END, cmsStageAllocMatrix(ContextID, 3, 3, (cmsFloat64Number*) &Mat, NULL));
        
        
        
        
        if (cmsGetPCS(hProfile) == cmsSigLabData) {

             cmsPipelineInsertStage(Lut, cmsAT_END, _cmsStageAllocXYZ2Lab(ContextID));
        }

    }

    return Lut;
}