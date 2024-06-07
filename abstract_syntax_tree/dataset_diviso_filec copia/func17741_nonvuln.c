lldpd_send(struct lldpd_hardware *hardware)
{
	struct lldpd *cfg = hardware->h_cfg;
	struct lldpd_port *port;
	int i, sent;

	if (cfg->g_config.c_receiveonly || cfg->g_config.c_paused) return;
	if ((hardware->h_flags & IFF_RUNNING) == 0)
		return;

	log_debug("STR", hardware->h_ifname);
	sent = 0;
	for (i=0; cfg->g_protocols[i].mode != 0; i++) {
		if (!cfg->g_protocols[i].enabled)
			continue;
		
		if (cfg->g_protocols[i].enabled > 1) {
			cfg->g_protocols[i].send(cfg, hardware);
			sent++;
			continue;
		}
		TAILQ_FOREACH(port, &hardware->h_rports, p_entries) {
			
			if (port->p_hidden_out)
				continue;
			if (port->p_protocol ==
			    cfg->g_protocols[i].mode) {
				TRACE(LLDPD_FRAME_SEND(hardware->h_ifname,
					cfg->g_protocols[i].name));
				log_debug("STR",
				    hardware->h_ifname,
				    cfg->g_protocols[i].name);
				cfg->g_protocols[i].send(cfg,
				    hardware);
				sent++;
				break;
			}
		}
	}

	if (!sent) {
		
		for (i = 0; cfg->g_protocols[i].mode != 0; i++) {
			if (!cfg->g_protocols[i].enabled) continue;
			TRACE(LLDPD_FRAME_SEND(hardware->h_ifname,
				cfg->g_protocols[i].name));
			log_debug("STR",
			    cfg->g_protocols[i].name, hardware->h_ifname);
			cfg->g_protocols[i].send(cfg,
			    hardware);
			break;
		}
		if (cfg->g_protocols[i].mode == 0)
			log_warnx("STR");
	}
}