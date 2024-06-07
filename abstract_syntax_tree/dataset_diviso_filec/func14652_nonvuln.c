cmsBool CMSEXPORT cmsStageSampleCLut16bit(cmsStage* mpe, cmsSAMPLER16 Sampler, void * Cargo, cmsUInt32Number dwFlags)
{
    int i, t, nTotalPoints, index, rest;
    int nInputs, nOutputs;
    cmsUInt32Number* nSamples;
    cmsUInt16Number In[MAX_INPUT_DIMENSIONS+1], Out[MAX_STAGE_CHANNELS];
    _cmsStageCLutData* clut;

    if (mpe == NULL) return FALSE;

    clut = (_cmsStageCLutData*) mpe->Data;

    if (clut == NULL) return FALSE;

    nSamples = clut->Params ->nSamples;
    nInputs  = clut->Params ->nInputs;
    nOutputs = clut->Params ->nOutputs;

    if (nInputs <= 0) return FALSE;
    if (nOutputs <= 0) return FALSE;
    if (nInputs > MAX_INPUT_DIMENSIONS) return FALSE;
    if (nOutputs >= MAX_STAGE_CHANNELS) return FALSE;

    nTotalPoints = CubeSize(nSamples, nInputs);
    if (nTotalPoints == 0) return FALSE;

    index = 0;
    for (i = 0; i < nTotalPoints; i++) {

        rest = i;
        for (t = nInputs-1; t >=0; --t) {

            cmsUInt32Number  Colorant = rest % nSamples[t];

            rest /= nSamples[t];

            In[t] = _cmsQuantizeVal(Colorant, nSamples[t]);
        }

        if (clut ->Tab.T != NULL) {
            for (t=0; t < nOutputs; t++)
                Out[t] = clut->Tab.T[index + t];
        }

        if (!Sampler(In, Out, Cargo))
            return FALSE;

        if (!(dwFlags & SAMPLER_INSPECT)) {

            if (clut ->Tab.T != NULL) {
                for (t=0; t < nOutputs; t++)
                    clut->Tab.T[index + t] = Out[t];
            }
        }

        index += nOutputs;
    }

    return TRUE;
}