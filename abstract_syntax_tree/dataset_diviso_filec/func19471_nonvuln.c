callbacks_bugs_activate (GtkMenuItem     *menuitem,
                             gpointer         user_data)
{
    int i;
    

    
    GtkWidget *bugs_dialog = gtk_dialog_new_with_buttons(_("STR"),
							 NULL,
							 GTK_DIALOG_DESTROY_WITH_PARENT,
							 GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
							 NULL);
    gtk_container_set_border_width (GTK_CONTAINER (bugs_dialog), 5);
    gtk_dialog_set_default_response (GTK_DIALOG(bugs_dialog),
				     GTK_RESPONSE_ACCEPT);
    g_signal_connect (G_OBJECT(bugs_dialog), "STR",
		      G_CALLBACK (gtk_widget_destroy), GTK_WIDGET(bugs_dialog));
    
    
    GString *bugs_string = g_string_new(NULL);
    for (i=0; bugs_string_array[i] != NULL; i++) {
	
	g_string_append_printf(bugs_string, "STR",
		(bugs_string_array[i][0] == '\0') ? "" : _(bugs_string_array[i]));
    }
    
    
    GtkWidget *bugs_label = gtk_label_new (bugs_string->str);
    g_string_free(bugs_string, FALSE);
    gtk_misc_set_alignment(GTK_MISC(bugs_label), 0, 0);
    gtk_misc_set_padding(GTK_MISC(bugs_label), 7, 7);
    
    
    GtkWidget *bugs_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(bugs_window),
                                          GTK_WIDGET(bugs_label));
    gtk_widget_set_size_request(bugs_window, 600, 300);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(bugs_dialog)->vbox),
                      GTK_WIDGET(bugs_window));

    gtk_widget_show_all(GTK_WIDGET(bugs_dialog));
    gtk_dialog_run(GTK_DIALOG(bugs_dialog));
    
}