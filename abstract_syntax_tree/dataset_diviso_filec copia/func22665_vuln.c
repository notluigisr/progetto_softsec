cmsBool ReadMPEElem(struct _cms_typehandler_struct* self,
                    cmsIOHANDLER* io,
                    void* Cargo,
                    cmsUInt32Number n,
                    cmsUInt32Number SizeOfTag)
{
    cmsStageSignature ElementSig;
    cmsTagTypeHandler* TypeHandler;
    cmsStage *mpe = NULL;
    cmsUInt32Number nItems;
    cmsPipeline *NewLUT = (cmsPipeline *) Cargo;

    
    if (!_cmsReadUInt32Number(io, (cmsUInt32Number*) &ElementSig)) return FALSE;

    
    if (!_cmsReadUInt32Number(io, NULL)) return FALSE;

    
    TypeHandler = GetHandler((cmsTagTypeSignature) ElementSig, SupportedMPEtypes);
    if (TypeHandler == NULL)  {

        char String[5];

        _cmsTagSignature2String(String, (cmsTagSignature) ElementSig);

        
        cmsSignalError(self ->ContextID, cmsERROR_UNKNOWN_EXTENSION, "STR", String);
        return FALSE;
    }

    
    
    if (TypeHandler ->ReadPtr != NULL) {

        
        mpe = (cmsStage*) TypeHandler ->ReadPtr(self, io, &nItems, SizeOfTag);
        if (mpe == NULL) return FALSE;

        
        cmsPipelineInsertStage(NewLUT, cmsAT_END, mpe);
    }

    return TRUE;

    cmsUNUSED_PARAMETER(SizeOfTag);
    cmsUNUSED_PARAMETER(n);
}