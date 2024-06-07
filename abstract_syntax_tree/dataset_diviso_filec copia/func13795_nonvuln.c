start_printer(cupsd_client_t  *con,	
              ipp_attribute_t *uri)	
{
  int			i;		
  http_status_t		status;		
  cups_ptype_t		dtype;		
  cupsd_printer_t	*printer;	


  cupsdLogMessage(CUPSD_LOG_DEBUG2, "STR", con,
                  con->number, uri->values[0].string.text);

 

  if (!cupsdValidateDest(uri->values[0].string.text, &dtype, &printer))
  {
   

    send_ipp_status(con, IPP_NOT_FOUND,
                    _("STR"));
    return;
  }

 

  if ((status = cupsdCheckPolicy(printer->op_policy_ptr, con, NULL)) != HTTP_OK)
  {
    send_http_error(con, status, printer);
    return;
  }

 

  printer->state_message[0] = '\0';

  cupsdStartPrinter(printer, 1);

  if (dtype & CUPS_PRINTER_CLASS)
    cupsdLogMessage(CUPSD_LOG_INFO, "STR",
                    printer->name, get_username(con));
  else
    cupsdLogMessage(CUPSD_LOG_INFO, "STR",
                    printer->name, get_username(con));

  cupsdCheckJobs();

 

  if ((i = check_quotas(con, printer)) < 0)
  {
    send_ipp_status(con, IPP_NOT_POSSIBLE, _("STR"));
    return;
  }
  else if (i == 0)
  {
    send_ipp_status(con, IPP_NOT_AUTHORIZED, _("STR"));
    return;
  }

 

  con->response->request.status.status_code = IPP_OK;
}