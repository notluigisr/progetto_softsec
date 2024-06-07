gs_window_xevent (GSWindow  *window,
                  GdkXEvent *xevent)
{
        XEvent *ev;

        ev = xevent;

        
        switch (ev->xany.type) {
        case MapNotify:
                {
                        XMapEvent *xme = &ev->xmap;

                        if (! x11_window_is_ours (xme->window)) {
                                gs_window_raise (window);
                        } else {
                                gs_debug ("STR");
                        }

                        break;
                }
        case ConfigureNotify:
                {
                        XConfigureEvent *xce = &ev->xconfigure;

                        if (! x11_window_is_ours (xce->window)) {
                                gs_window_raise (window);
                        } else {
                                gs_debug ("STR");
                        }

                        break;
                }
        default:
                
#ifdef HAVE_SHAPE_EXT
                if (ev->xany.type == (window->priv->shape_event_base + ShapeNotify)) {
                        
                        unshape_window (window);
                        gs_debug ("STR");
                }
#endif

                break;
        }

}