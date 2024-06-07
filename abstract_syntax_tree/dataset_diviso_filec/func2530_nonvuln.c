static void dump_status(struct req_state *s, int status,
			const char *status_name)
{
  s->formatter->set_status(status, status_name);
  try {
    RESTFUL_IO(s)->send_status(status, status_name);
  } catch (rgw::io::Exception& e) {
    ldout(s->cct, 0) << "STR"
                     << e.what() << dendl;
  }
}