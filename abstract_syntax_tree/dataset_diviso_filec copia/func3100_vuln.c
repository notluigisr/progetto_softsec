cmsBool AddConversion(cmsPipeline* Result, cmsColorSpaceSignature InPCS, cmsColorSpaceSignature OutPCS, cmsMAT3* m, cmsVEC3* off)
{
    cmsFloat64Number* m_as_dbl = (cmsFloat64Number*) m;
    cmsFloat64Number* off_as_dbl = (cmsFloat64Number*) off;

    
    switch (InPCS) {

        case cmsSigXYZData: 

            switch (OutPCS) {

            case cmsSigXYZData:  
                if (!IsEmptyLayer(m, off))
                    cmsPipelineInsertStage(Result, cmsAT_END, cmsStageAllocMatrix(Result ->ContextID, 3, 3, m_as_dbl, off_as_dbl));
                break;

            case cmsSigLabData:  
                if (!IsEmptyLayer(m, off))
                    cmsPipelineInsertStage(Result, cmsAT_END, cmsStageAllocMatrix(Result ->ContextID, 3, 3, m_as_dbl, off_as_dbl));
                cmsPipelineInsertStage(Result, cmsAT_END, _cmsStageAllocXYZ2Lab(Result ->ContextID));
                break;

            default:
                return FALSE;   
                }
                break;


        case cmsSigLabData: 

            switch (OutPCS) {

            case cmsSigXYZData:  

                cmsPipelineInsertStage(Result, cmsAT_END, _cmsStageAllocLab2XYZ(Result ->ContextID));
                if (!IsEmptyLayer(m, off))
                    cmsPipelineInsertStage(Result, cmsAT_END, cmsStageAllocMatrix(Result ->ContextID, 3, 3, m_as_dbl, off_as_dbl));
                break;

            case cmsSigLabData:  

                if (!IsEmptyLayer(m, off)) {
                    cmsPipelineInsertStage(Result, cmsAT_END, _cmsStageAllocLab2XYZ(Result ->ContextID));
                    cmsPipelineInsertStage(Result, cmsAT_END, cmsStageAllocMatrix(Result ->ContextID, 3, 3, m_as_dbl, off_as_dbl));
                    cmsPipelineInsertStage(Result, cmsAT_END, _cmsStageAllocXYZ2Lab(Result ->ContextID));
                }
                break;

            default:
                return FALSE;  
            }
            break;


            
        default:
            if (InPCS != OutPCS) return FALSE;
            break;
    }

    return TRUE;
}