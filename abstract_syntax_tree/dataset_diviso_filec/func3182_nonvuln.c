translate_hierarchy_event (ClutterBackendX11       *backend_x11,
                           ClutterDeviceManagerXI2 *manager_xi2,
                           XIHierarchyEvent        *ev)
{
  int i;

  for (i = 0; i < ev->num_info; i++)
    {
      if (ev->info[i].flags & XIDeviceEnabled)
        {
          XIDeviceInfo *info;
          int n_devices;

          CLUTTER_NOTE (EVENT, "STR");

          clutter_x11_trap_x_errors ();
          info = XIQueryDevice (backend_x11->xdpy,
                                ev->info[i].deviceid,
                                &n_devices);
          clutter_x11_untrap_x_errors ();
          if (info != NULL)
            {
              add_device (manager_xi2, backend_x11, &info[0], FALSE);
              XIFreeDeviceInfo (info);
            }
        }
      else if (ev->info[i].flags & XIDeviceDisabled)
        {
          CLUTTER_NOTE (EVENT, "STR");

          remove_device (manager_xi2, ev->info[i].deviceid);
        }
      else if ((ev->info[i].flags & XISlaveAttached) ||
               (ev->info[i].flags & XISlaveDetached))
        {
          ClutterInputDevice *master, *slave;
          XIDeviceInfo *info;
          int n_devices;
          gboolean send_changed = FALSE;

          CLUTTER_NOTE (EVENT, "STR",
                        (ev->info[i].flags & XISlaveAttached)
                          ? "STR"
                          : "STR");

          slave = g_hash_table_lookup (manager_xi2->devices_by_id,
                                       GINT_TO_POINTER (ev->info[i].deviceid));
          master = clutter_input_device_get_associated_device (slave);

          
          if (master != NULL)
            {
              _clutter_input_device_remove_slave (master, slave);
              _clutter_input_device_set_associated_device (slave, NULL);

              send_changed = TRUE;
            }

          
          if (ev->info[i].flags & XISlaveAttached)
            {
              clutter_x11_trap_x_errors ();
              info = XIQueryDevice (backend_x11->xdpy,
                                    ev->info[i].deviceid,
                                    &n_devices);
              clutter_x11_untrap_x_errors ();
              if (info != NULL)
                {
                  master = g_hash_table_lookup (manager_xi2->devices_by_id,
                                                GINT_TO_POINTER (info->attachment));
                  if (master != NULL)
                    {
                      _clutter_input_device_set_associated_device (slave, master);
                      _clutter_input_device_add_slave (master, slave);

                      send_changed = TRUE;
                    }
                  XIFreeDeviceInfo (info);
                }
            }

          if (send_changed)
            {
              ClutterStage *stage = _clutter_input_device_get_stage (master);
              if (stage != NULL)
                _clutter_stage_x11_events_device_changed (CLUTTER_STAGE_X11 (_clutter_stage_get_window (stage)), 
                                                          master,
                                                          CLUTTER_DEVICE_MANAGER (manager_xi2));
            }
        }
    }
}