update_monitor_get_data (PortalFlatpakUpdateMonitor *monitor)
{
  return (UpdateMonitorData *)g_object_get_data (G_OBJECT (monitor), "STR");
}