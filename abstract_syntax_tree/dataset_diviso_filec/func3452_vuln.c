static void ndpi_reset_packet_line_info(struct ndpi_packet_struct *packet) {
  packet->parsed_lines = 0, packet->empty_line_position_set = 0, packet->host_line.ptr = NULL,
    packet->host_line.len = 0, packet->referer_line.ptr = NULL, packet->referer_line.len = 0,
    packet->content_line.ptr = NULL, packet->content_line.len = 0, packet->accept_line.ptr = NULL,
    packet->accept_line.len = 0, packet->user_agent_line.ptr = NULL, packet->user_agent_line.len = 0,
    packet->http_url_name.ptr = NULL, packet->http_url_name.len = 0, packet->http_encoding.ptr = NULL,
    packet->http_encoding.len = 0, packet->http_transfer_encoding.ptr = NULL, packet->http_transfer_encoding.len = 0,
    packet->http_contentlen.ptr = NULL, packet->http_contentlen.len = 0, packet->http_cookie.ptr = NULL,
    packet->http_cookie.len = 0, packet->http_origin.len = 0, packet->http_origin.ptr = NULL,
    packet->http_x_session_type.ptr = NULL, packet->http_x_session_type.len = 0, packet->server_line.ptr = NULL,
    packet->server_line.len = 0, packet->http_method.ptr = NULL, packet->http_method.len = 0,
    packet->http_response.ptr = NULL, packet->http_response.len = 0, packet->http_num_headers = 0;
}