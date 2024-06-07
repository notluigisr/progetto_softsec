cmsBool ComputeConversion(int i, cmsHPROFILE hProfiles[],
                                 cmsUInt32Number Intent,
                                 cmsBool BPC,
                                 cmsFloat64Number AdaptationState,
                                 cmsMAT3* m, cmsVEC3* off)
{

    int k;

    
    _cmsMAT3identity(m);
    _cmsVEC3init(off, 0, 0, 0);

    
    if (Intent == INTENT_ABSOLUTE_COLORIMETRIC) {

        cmsCIEXYZ WhitePointIn, WhitePointOut;
        cmsMAT3 ChromaticAdaptationMatrixIn, ChromaticAdaptationMatrixOut;

        _cmsReadMediaWhitePoint(&WhitePointIn,  hProfiles[i-1]);
        _cmsReadCHAD(&ChromaticAdaptationMatrixIn, hProfiles[i-1]);

        _cmsReadMediaWhitePoint(&WhitePointOut,  hProfiles[i]);
        _cmsReadCHAD(&ChromaticAdaptationMatrixOut, hProfiles[i]);

        if (!ComputeAbsoluteIntent(AdaptationState,
                                  &WhitePointIn,  &ChromaticAdaptationMatrixIn,
                                  &WhitePointOut, &ChromaticAdaptationMatrixOut, m)) return FALSE;

    }
    else {
        

        if (BPC) {

            cmsCIEXYZ BlackPointIn, BlackPointOut;

            cmsDetectBlackPoint(&BlackPointIn,  hProfiles[i-1], Intent, 0);
            cmsDetectDestinationBlackPoint(&BlackPointOut, hProfiles[i], Intent, 0);

            
            if (BlackPointIn.X != BlackPointOut.X ||
                BlackPointIn.Y != BlackPointOut.Y ||
                BlackPointIn.Z != BlackPointOut.Z)
                    ComputeBlackPointCompensation(&BlackPointIn, &BlackPointOut, m, off);
        }
    }

    
    
    
    
    
    
    
    

    for (k=0; k < 3; k++) {
        off ->n[k] /= MAX_ENCODEABLE_XYZ;
    }

    return TRUE;
}