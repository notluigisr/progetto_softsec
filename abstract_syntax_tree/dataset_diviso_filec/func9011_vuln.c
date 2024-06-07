cmsBool ReadPositionTable(struct _cms_typehandler_struct* self,
                              cmsIOHANDLER* io,
                              cmsUInt32Number Count,
                              cmsUInt32Number BaseOffset,
                              void *Cargo,
                              PositionTableEntryFn ElementFn)
{
    cmsUInt32Number i;
    cmsUInt32Number *ElementOffsets = NULL, *ElementSizes = NULL;

    
    ElementOffsets = (cmsUInt32Number *) _cmsCalloc(io ->ContextID, Count, sizeof(cmsUInt32Number *));
    if (ElementOffsets == NULL) goto Error;

    ElementSizes = (cmsUInt32Number *) _cmsCalloc(io ->ContextID, Count, sizeof(cmsUInt32Number *));
    if (ElementSizes == NULL) goto Error;

    for (i=0; i < Count; i++) {

        if (!_cmsReadUInt32Number(io, &ElementOffsets[i])) goto Error;
        if (!_cmsReadUInt32Number(io, &ElementSizes[i])) goto Error;

        ElementOffsets[i] += BaseOffset;
    }

    
    for (i=0; i < Count; i++) {

        if (!io -> Seek(io, ElementOffsets[i])) goto Error;

        
        if (!ElementFn(self, io, Cargo, i, ElementSizes[i])) goto Error;
    }

    
    if (ElementOffsets != NULL) _cmsFree(io ->ContextID, ElementOffsets);
    if (ElementSizes != NULL) _cmsFree(io ->ContextID, ElementSizes);
    return TRUE;

Error:
    if (ElementOffsets != NULL) _cmsFree(io ->ContextID, ElementOffsets);
    if (ElementSizes != NULL) _cmsFree(io ->ContextID, ElementSizes);
    return FALSE;
}