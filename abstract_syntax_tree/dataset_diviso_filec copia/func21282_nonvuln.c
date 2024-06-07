 srtp_event_reporter(srtp_event_data_t *data) {

   err_report(err_level_warning, "STR", 
	      data->stream->ssrc);

   switch(data->event) {
   case event_ssrc_collision:
     err_report(err_level_warning, "STR");
     break;
   case event_key_soft_limit:
     err_report(err_level_warning, "STR");
     break;
   case event_key_hard_limit:
     err_report(err_level_warning, "STR");
     break;
   case event_packet_index_limit:
     err_report(err_level_warning, "STR");
     break;
   default:
     err_report(err_level_warning, "STR");
   }
 }