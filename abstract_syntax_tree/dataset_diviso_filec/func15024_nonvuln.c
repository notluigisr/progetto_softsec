OSD::~OSD()
{
  delete authorize_handler_cluster_registry;
  delete authorize_handler_service_registry;
  delete class_handler;
  cct->get_perfcounters_collection()->remove(recoverystate_perf);
  cct->get_perfcounters_collection()->remove(logger);
  delete recoverystate_perf;
  delete logger;
  delete store;
}