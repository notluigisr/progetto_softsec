void vnc_client_error(VncState *vs)
{
    VNC_DEBUG("STR");
    vnc_disconnect_start(vs);
}