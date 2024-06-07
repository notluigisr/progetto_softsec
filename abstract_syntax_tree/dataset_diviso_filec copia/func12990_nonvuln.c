static CURLcode smtp_perform_command(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;

  
  if(smtp->rcpt)
    result = Curl_pp_sendf(&conn->proto.smtpc.pp, "STR",
                           smtp->custom && smtp->custom[0] != '\0' ?
                           smtp->custom : "STR",
                           smtp->rcpt->data);
  else
    result = Curl_pp_sendf(&conn->proto.smtpc.pp, "STR",
                           smtp->custom && smtp->custom[0] != '\0' ?
                           smtp->custom : "STR");

  if(!result)
    state(conn, SMTP_COMMAND);

  return result;
}