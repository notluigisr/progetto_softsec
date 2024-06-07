static void window_resize(IMAGE *img)
{
    gtk_drawing_area_size(GTK_DRAWING_AREA (img->darea),
        img->width, img->height);
    if (!(GTK_WIDGET_FLAGS(img->window) & GTK_VISIBLE)) {
        
        gtk_window_set_default_size(GTK_WINDOW(img->window),
            min(gdk_screen_width()-96, img->width+24),
            min(gdk_screen_height()-96, img->height+24));
    }
}