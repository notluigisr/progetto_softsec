int Monitor::init()
{
  dout(2) << "STR" << dendl;
  Mutex::Locker l(lock);

  finisher.start();

  
  timer.init();
  new_tick();

  cpu_tp.start();

  
  messenger->add_dispatcher_tail(this);

  mgr_client.init();
  mgr_messenger->add_dispatcher_tail(&mgr_client);
  mgr_messenger->add_dispatcher_tail(this);  

  bootstrap();
  
  session_map.feature_map.add_mon(con_self->get_features());
  return 0;
}