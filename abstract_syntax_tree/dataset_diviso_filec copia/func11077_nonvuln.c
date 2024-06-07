writeDataPDU(PRIVATE_ASSOCIATIONKEY ** association,
             DUL_DATAPDU * pdu)
{
    unsigned char
        head[24];
    unsigned long
        length;
    int
        nbytes;

    
    
    
    
    OFCondition cond = streamDataPDUHead(pdu, head, sizeof(head), &length);
    if (cond.bad()) return cond;

    
    do
    {
      nbytes = (*association)->connection ? (*association)->connection->write((char*)head, size_t(length)) : 0;
    } while (nbytes == -1 && OFStandard::getLastNetworkErrorCode().value() == DCMNET_EINTR);

    
    if ((unsigned long) nbytes != length)
    {
        OFString msg = "STR";
        msg += OFStandard::getLastNetworkErrorCode().message();
        msg += "STR";
        return makeDcmnetCondition(DULC_TCPIOERROR, OF_error, msg.c_str());
    }

    
    do
    {
      nbytes = (*association)->connection ? (*association)->connection->write((char*)pdu->presentationDataValue.data,
        size_t(pdu->presentationDataValue.length - 2)) : 0;
    } while (nbytes == -1 && OFStandard::getLastNetworkErrorCode().value() == DCMNET_EINTR);

        
    if ((unsigned long) nbytes != pdu->presentationDataValue.length - 2)
    {
        OFString msg = "STR";
        msg += OFStandard::getLastNetworkErrorCode().message();
        msg += "STR";
        return makeDcmnetCondition(DULC_TCPIOERROR, OF_error, msg.c_str());
    }

    
    return EC_Normal;
}