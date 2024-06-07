OFCondition DcmSCP::receiveDIMSECommand(T_ASC_PresentationContextID *presID,
                                        T_DIMSE_Message *message,
                                        DcmDataset **statusDetail,
                                        DcmDataset **commandSet,
                                        const Uint32 timeout)
{
  if (m_assoc == NULL)
    return DIMSE_ILLEGALASSOCIATION;

  OFCondition cond;
  if (timeout > 0)
  {
    
    cond = DIMSE_receiveCommand(m_assoc, DIMSE_NONBLOCKING, timeout, presID,
                                message, statusDetail, commandSet);
  } else {
    
    cond = DIMSE_receiveCommand(m_assoc, m_cfg->getDIMSEBlockingMode(), m_cfg->getDIMSETimeout(), presID,
                                message, statusDetail, commandSet);
  }
  return cond;
}