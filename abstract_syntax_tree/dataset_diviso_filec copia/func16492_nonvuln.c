void vnc_display_init(DisplayState *ds)
{
    VncDisplay *vs = g_malloc0(sizeof(*vs));

    dcl = g_malloc0(sizeof(DisplayChangeListener));

    ds->opaque = vs;
    dcl->idle = 1;
    vnc_display = vs;

    vs->lsock = -1;

    vs->ds = ds;
    QTAILQ_INIT(&vs->clients);
    vs->expires = TIME_MAX;

    if (keyboard_layout)
        vs->kbd_layout = init_keyboard_layout(name2keysym, keyboard_layout);
    else
        vs->kbd_layout = init_keyboard_layout(name2keysym, "STR");

    if (!vs->kbd_layout)
        exit(1);

    qemu_mutex_init(&vs->mutex);
    vnc_start_worker_thread();

    dcl->dpy_gfx_copy = vnc_dpy_copy;
    dcl->dpy_gfx_update = vnc_dpy_update;
    dcl->dpy_gfx_resize = vnc_dpy_resize;
    dcl->dpy_gfx_setdata = vnc_dpy_setdata;
    dcl->dpy_mouse_set = vnc_mouse_set;
    dcl->dpy_cursor_define = vnc_dpy_cursor_define;
    register_displaychangelistener(ds, dcl);
}