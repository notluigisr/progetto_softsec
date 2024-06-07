cmsBool  CMSEXPORT cmsPipelineCheckAndRetreiveStages(const cmsPipeline* Lut, cmsUInt32Number n, ...)
{
    va_list args;
    cmsUInt32Number i;
    cmsStage* mpe;
    cmsStageSignature Type;
    void** ElemPtr;

    
    if (cmsPipelineStageCount(Lut) != n) return FALSE;

    va_start(args, n);

    
    mpe = Lut ->Elements;
    for (i=0; i < n; i++) {

        
        Type  = (cmsStageSignature)va_arg(args, cmsStageSignature);
        if (mpe ->Type != Type) {

            va_end(args);       
            return FALSE;
        }
        mpe = mpe ->Next;
    }

    
    mpe = Lut ->Elements;
    for (i=0; i < n; i++) {

        ElemPtr = va_arg(args, void**);
        if (ElemPtr != NULL)
            *ElemPtr = mpe;

        mpe = mpe ->Next;
    }

    va_end(args);
    return TRUE;
}