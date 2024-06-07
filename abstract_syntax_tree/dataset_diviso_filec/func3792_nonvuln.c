AE_6_ExamineAssociateRequest(PRIVATE_NETWORKKEY ** ,
         PRIVATE_ASSOCIATIONKEY ** association, int , void *params)
{
    DUL_ASSOCIATESERVICEPARAMETERS
    * service;
    unsigned char
        *buffer=NULL,
        pduType,
        pduReserve;
    unsigned long
        pduLength;
    PRV_ASSOCIATEPDU
        assoc;

    (*association)->timerStart = 0;
    service = (DUL_ASSOCIATESERVICEPARAMETERS *) params;
    OFCondition cond = readPDU(association, DUL_BLOCK, 0, &buffer,
                   &pduType, &pduReserve, &pduLength);

    if (cond.bad())
    {
       if (buffer) free(buffer);
       return cond;
    }

    

    if (pduType == DUL_TYPEASSOCIATERQ)
    {
        if ((*association)->associatePDUFlag)
        {
          
          (*association)->associatePDU = new char[pduLength+6];
          if ((*association)->associatePDU)
          {
            memcpy((*association)->associatePDU, buffer, (size_t) pduLength+6);
            (*association)->associatePDULength = pduLength+6;
          }
        }

        DCMNET_DEBUG(dump_pdu("STR", buffer, pduLength + 6));
        cond = parseAssociate(buffer, pduLength, &assoc);
        free(buffer);
        buffer = NULL;

        if (cond.bad()) {
            if (cond == DUL_UNSUPPORTEDPEERPROTOCOL)    
                (*association)->protocolState = STATE3;
            return cond;
        }
        OFStandard::strlcpy(service->calledAPTitle, assoc.calledAPTitle, sizeof(service->calledAPTitle));
        OFStandard::strlcpy(service->callingAPTitle, assoc.callingAPTitle, sizeof(service->callingAPTitle));
        OFStandard::strlcpy(service->applicationContextName, assoc.applicationContext.data, sizeof(service->applicationContextName));

        if ((service->requestedPresentationContext = LST_Create()) == NULL) return EC_MemoryExhausted;
        if (translatePresentationContextList(&assoc.presentationContextList,
                                             &assoc.userInfo.SCUSCPRoleList,
                                             &service->requestedPresentationContext).bad())
        {
            return DUL_PCTRANSLATIONFAILURE;
        }

        
        if (assoc.userInfo.extNegList != NULL) {
            service->requestedExtNegList = new SOPClassExtendedNegotiationSubItemList;
            if (service->requestedExtNegList == NULL) return EC_MemoryExhausted;
            appendList(*assoc.userInfo.extNegList, *service->requestedExtNegList);
        }

        
        if (assoc.userInfo.usrIdent != NULL) {
          service->reqUserIdentNeg = new UserIdentityNegotiationSubItemRQ();
          if (service->reqUserIdentNeg == NULL) return EC_MemoryExhausted;
            *(service->reqUserIdentNeg) = *(OFstatic_cast(UserIdentityNegotiationSubItemRQ*,assoc.userInfo.usrIdent));
        }

        service->peerMaxPDU = assoc.userInfo.maxLength.maxLength;
        (*association)->maxPDV = assoc.userInfo.maxLength.maxLength;
        (*association)->maxPDVRequestor =
            assoc.userInfo.maxLength.maxLength;
        OFStandard::strlcpy(service->callingImplementationClassUID,
               assoc.userInfo.implementationClassUID.data, DICOM_UI_LENGTH + 1);
        OFStandard::strlcpy(service->callingImplementationVersionName,
               assoc.userInfo.implementationVersionName.data, 16 + 1);
        (*association)->associationState = DUL_ASSOC_ESTABLISHED;

        destroyPresentationContextList(&assoc.presentationContextList);
        destroyUserInformationLists(&assoc.userInfo);

        
        (*association)->protocolState = STATE3;

        return EC_Normal;
    }
    return DUL_UNEXPECTEDPDU;
}