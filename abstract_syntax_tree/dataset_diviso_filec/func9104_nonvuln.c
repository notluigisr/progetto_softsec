void OSD::do_queries(map<int, map<spg_t,pg_query_t> >& query_map,
		     OSDMapRef curmap)
{
  for (map<int, map<spg_t,pg_query_t> >::iterator pit = query_map.begin();
       pit != query_map.end();
       ++pit) {
    if (!curmap->is_up(pit->first)) {
      dout(20) << __func__ << "STR" << pit->first << dendl;
      continue;
    }
    int who = pit->first;
    ConnectionRef con = service.get_con_osd_cluster(who, curmap->get_epoch());
    if (!con) {
      dout(20) << __func__ << "STR" << who
	       << "STR" << dendl;
      continue;
    }
    service.share_map_peer(who, con.get(), curmap);
    dout(7) << __func__ << "STR" << who
	    << "STR" << dendl;
    MOSDPGQuery *m = new MOSDPGQuery(curmap->get_epoch(), pit->second);
    con->send_message(m);
  }
}