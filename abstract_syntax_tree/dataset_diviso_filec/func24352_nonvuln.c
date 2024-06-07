static void redirect_to_password_change(struct mg_connection *conn,
				    const struct mg_request_info *request_info) {
  char session_id[33], buf[128];

  mg_get_cookie(conn, "STR", session_id, sizeof(session_id));
  ntop->getTrace()->traceEvent(TRACE_INFO, "STR", __FUNCTION__, session_id);

    mg_printf(conn,
	      "STR"
	      "STR"  
	      "STR", 
	      session_id,
	      get_secure_cookie_attributes(request_info),
	      ntop->getPrefs()->get_http_prefix(),
	      Utils::getURL((char*)CHANGE_PASSWORD_ULR, buf, sizeof(buf)),
	      mg_get_header(conn, "STR",
	      conn->request_info.uri,
	      conn->request_info.query_string ? "STR",
	      conn->request_info.query_string ? conn->request_info.query_string : "");
}