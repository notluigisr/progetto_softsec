static void vnc_connect(VncDisplay *vd, QIOChannelSocket *sioc,
                        bool skipauth, bool websocket)
{
    VncState *vs = g_new0(VncState, 1);
    bool first_client = QTAILQ_EMPTY(&vd->clients);
    int i;

    vs->sioc = sioc;
    object_ref(OBJECT(vs->sioc));
    vs->ioc = QIO_CHANNEL(sioc);
    object_ref(OBJECT(vs->ioc));
    vs->vd = vd;

    buffer_init(&vs->input,          "STR", sioc);
    buffer_init(&vs->output,         "STR", sioc);
    buffer_init(&vs->jobs_buffer,    "STR", sioc);

    buffer_init(&vs->tight.tight,    "STR", sioc);
    buffer_init(&vs->tight.zlib,     "STR", sioc);
    buffer_init(&vs->tight.gradient, "STR", sioc);
#ifdef CONFIG_VNC_JPEG
    buffer_init(&vs->tight.jpeg,     "STR", sioc);
#endif
#ifdef CONFIG_VNC_PNG
    buffer_init(&vs->tight.png,      "STR", sioc);
#endif
    buffer_init(&vs->zlib.zlib,      "STR", sioc);
    buffer_init(&vs->zrle.zrle,      "STR", sioc);
    buffer_init(&vs->zrle.fb,        "STR", sioc);
    buffer_init(&vs->zrle.zlib,      "STR", sioc);

    if (skipauth) {
	vs->auth = VNC_AUTH_NONE;
	vs->subauth = VNC_AUTH_INVALID;
    } else {
        if (websocket) {
            vs->auth = vd->ws_auth;
            vs->subauth = VNC_AUTH_INVALID;
        } else {
            vs->auth = vd->auth;
            vs->subauth = vd->subauth;
        }
    }
    VNC_DEBUG("STR",
              sioc, websocket, vs->auth, vs->subauth);

    vs->lossy_rect = g_malloc0(VNC_STAT_ROWS * sizeof (*vs->lossy_rect));
    for (i = 0; i < VNC_STAT_ROWS; ++i) {
        vs->lossy_rect[i] = g_new0(uint8_t, VNC_STAT_COLS);
    }

    VNC_DEBUG("STR", vs->sioc);
    update_displaychangelistener(&vd->dcl, VNC_REFRESH_INTERVAL_BASE);
    qio_channel_set_blocking(vs->ioc, false, NULL);
    if (websocket) {
        vs->websocket = 1;
        if (vd->tlscreds) {
            vs->ioc_tag = qio_channel_add_watch(
                vs->ioc, G_IO_IN, vncws_tls_handshake_io, vs, NULL);
        } else {
            vs->ioc_tag = qio_channel_add_watch(
                vs->ioc, G_IO_IN, vncws_handshake_io, vs, NULL);
        }
    } else {
        vs->ioc_tag = qio_channel_add_watch(
            vs->ioc, G_IO_IN, vnc_client_io, vs, NULL);
    }

    vnc_client_cache_addr(vs);
    vnc_qmp_event(vs, QAPI_EVENT_VNC_CONNECTED);
    vnc_set_share_mode(vs, VNC_SHARE_MODE_CONNECTING);

    vs->last_x = -1;
    vs->last_y = -1;

    vs->as.freq = 44100;
    vs->as.nchannels = 2;
    vs->as.fmt = AUD_FMT_S16;
    vs->as.endianness = 0;

    qemu_mutex_init(&vs->output_mutex);
    vs->bh = qemu_bh_new(vnc_jobs_bh, vs);

    QTAILQ_INSERT_TAIL(&vd->clients, vs, next);
    if (first_client) {
        vnc_update_server_surface(vd);
    }

    graphic_hw_update(vd->dcl.con);

    if (!vs->websocket) {
        vnc_start_protocol(vs);
    }

    if (vd->num_connecting > vd->connections_limit) {
        QTAILQ_FOREACH(vs, &vd->clients, next) {
            if (vs->share_mode == VNC_SHARE_MODE_CONNECTING) {
                vnc_disconnect_start(vs);
                return;
            }
        }
    }
}