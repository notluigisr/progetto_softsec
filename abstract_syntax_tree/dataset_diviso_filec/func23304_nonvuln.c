cmsFloat32Number CMSEXPORT cmsEvalToneCurveFloat(const cmsToneCurve* Curve, cmsFloat32Number v)
{
    _cmsAssert(Curve != NULL);

    
    if (Curve ->nSegments == 0) {

        cmsUInt16Number In, Out;

        In = (cmsUInt16Number) _cmsQuickSaturateWord(v * 65535.0);
        Out = cmsEvalToneCurve16(Curve, In);

        return (cmsFloat32Number) (Out / 65535.0);
    }

    return (cmsFloat32Number) EvalSegmentedFn(Curve, v);
}