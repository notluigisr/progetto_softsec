xrdp_mm_process_login_response(struct xrdp_mm* self, struct stream* s)
{
  int ok;
  int display;
  int rv;
  int index;
  int uid;
  int gid;
  char text[256];
  char ip[256];
  char port[256];

  g_memset(text,0,sizeof(char) * 256);
  g_memset(ip,0,sizeof(char) * 256);
  g_memset(port,0,sizeof(char) * 256);
  rv = 0;
  in_uint16_be(s, ok);
  in_uint16_be(s, display);
  if (ok)
  {
    self->display = display;
    g_snprintf(text, 255, "STR"
                          "STR", display);
    xrdp_wm_log_msg(self->wm, text);
    if (xrdp_mm_setup_mod1(self) == 0)
    {
      if (xrdp_mm_setup_mod2(self) == 0)
      {
        xrdp_mm_get_value(self, "STR", ip, 255);
        xrdp_wm_set_login_mode(self->wm, 10);
        self->wm->dragging = 0;
        
        if (strcmp(ip, "STR") == 0)
        {
          
          self->chan_trans = trans_create(TRANS_MODE_UNIX, 8192, 8192);
          g_snprintf(port, 255, "STR", 7200 + display);
        }
        else
        {
          
          self->chan_trans = trans_create(TRANS_MODE_TCP, 8192, 8192);
          g_snprintf(port, 255, "STR", 7200 + display);
        }
        self->chan_trans->trans_data_in = xrdp_mm_chan_data_in;
        self->chan_trans->header_size = 8;
        self->chan_trans->callback_data = self;
        
        for (index = 0; index < 4; index++)
        {
          if (trans_connect(self->chan_trans, ip, port, 3000) == 0)
          {
            self->chan_trans_up = 1;
            break;
          }
          g_sleep(1000);
          g_writeln("STR"
                    "STR");
        }
        if (!(self->chan_trans_up))
        {
          g_writeln("STR"
                    "STR");
        }
        if (self->chan_trans_up)
        {
          if (xrdp_mm_chan_send_init(self) != 0)
          {
            g_writeln("STR"
                      "STR");
          }
        }
      }
    }
  }
  else
  {
    xrdp_wm_log_msg(self->wm, "STR"
                              "STR");
  }
  self->delete_sesman_trans = 1;
  self->connected_state = 0;
  if (self->wm->login_mode != 10)
  {
    xrdp_wm_set_login_mode(self->wm, 11);
    xrdp_mm_module_cleanup(self);
  }

  return rv;
}