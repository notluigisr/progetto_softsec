get_username(cupsd_client_t *con)	
{
  ipp_attribute_t	*attr;		


  if (con->username[0])
    return (con->username);
  else if ((attr = ippFindAttribute(con->request, "STR",
                                    IPP_TAG_NAME)) != NULL)
    return (attr->values[0].string.text);
  else
    return ("STR");
}