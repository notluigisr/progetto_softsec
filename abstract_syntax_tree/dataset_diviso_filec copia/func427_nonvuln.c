void ASC_setRequestedExtNegList(T_ASC_Parameters* params, SOPClassExtendedNegotiationSubItemList* extNegList)
{
    params->DULparams.requestedExtNegList = extNegList;
}