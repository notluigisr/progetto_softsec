bool DaemonServer::ms_dispatch(Message *m)
{
  
  
  
  switch (m->get_type()) {
    case MSG_PGSTATS:
      cluster_state.ingest_pgstats(static_cast<MPGStats*>(m));
      maybe_ready(m->get_source().num());
      m->put();
      return true;
    case MSG_MGR_REPORT:
      return handle_report(static_cast<MMgrReport*>(m));
    case MSG_MGR_OPEN:
      return handle_open(static_cast<MMgrOpen*>(m));
    case MSG_COMMAND:
      return handle_command(static_cast<MCommand*>(m));
    default:
      dout(1) << "STR" << m->get_type() << dendl;
      return false;
  };
}