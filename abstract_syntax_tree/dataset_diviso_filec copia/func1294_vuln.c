cmsPipeline* BuildRGBOutputMatrixShaper(cmsHPROFILE hProfile)
{
    cmsPipeline* Lut;
    cmsToneCurve *Shapes[3], *InvShapes[3];
    cmsMAT3 Mat, Inv;
    int i, j;
    cmsContext ContextID = cmsGetProfileContextID(hProfile);

    if (!ReadICCMatrixRGB2XYZ(&Mat, hProfile))
        return NULL;

    if (!_cmsMAT3inverse(&Mat, &Inv))
        return NULL;

    
    
    

    for (i=0; i < 3; i++)
        for (j=0; j < 3; j++)
            Inv.v[i].n[j] *= OutpAdj;

    Shapes[0] = (cmsToneCurve *) cmsReadTag(hProfile, cmsSigRedTRCTag);
    Shapes[1] = (cmsToneCurve *) cmsReadTag(hProfile, cmsSigGreenTRCTag);
    Shapes[2] = (cmsToneCurve *) cmsReadTag(hProfile, cmsSigBlueTRCTag);

    if (!Shapes[0] || !Shapes[1] || !Shapes[2])
        return NULL;

    InvShapes[0] = cmsReverseToneCurve(Shapes[0]);
    InvShapes[1] = cmsReverseToneCurve(Shapes[1]);
    InvShapes[2] = cmsReverseToneCurve(Shapes[2]);

    if (!InvShapes[0] || !InvShapes[1] || !InvShapes[2]) {
        return NULL;
    }

    Lut = cmsPipelineAlloc(ContextID, 3, 3);
    if (Lut != NULL) {

        
        
        
        if (cmsGetPCS(hProfile) == cmsSigLabData) {

             cmsPipelineInsertStage(Lut, cmsAT_END, _cmsStageAllocLab2XYZ(ContextID));
        }

        cmsPipelineInsertStage(Lut, cmsAT_END, cmsStageAllocMatrix(ContextID, 3, 3, (cmsFloat64Number*) &Inv, NULL));
        cmsPipelineInsertStage(Lut, cmsAT_END, cmsStageAllocToneCurves(ContextID, 3, InvShapes));
    }

    cmsFreeToneCurveTriple(InvShapes);
    return Lut;
}