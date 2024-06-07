static void clear_warnings(void)
{
    
    if (!g_warning_issued)
        return;

    gtk_widget_hide(g_widget_warnings_area);
    gtk_container_foreach(GTK_CONTAINER(g_box_warning_labels), &remove_child_widget, NULL);
    g_warning_issued = false;
}