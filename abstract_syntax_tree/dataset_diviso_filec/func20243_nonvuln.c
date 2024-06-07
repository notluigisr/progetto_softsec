OFCondition DcmSCP::negotiateAssociation()
{
  
  if (m_assoc == NULL)
    return DIMSE_ILLEGALASSOCIATION;

  
  OFCondition result = m_cfg->evaluateIncomingAssociation(*m_assoc);
  if (result.bad())
  {
    OFString tempStr;
    DCMNET_ERROR(DimseCondition::dump(tempStr, result));
  }
  return result;
}