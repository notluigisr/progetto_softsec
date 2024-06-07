callbacks_display_object_properties_clicked (GtkButton *button, gpointer user_data)
{
	gint index = callbacks_get_selected_row_index ();
	guint i;

	if (index < 0 || selection_length (&screen.selectionInfo) == 0) {
		interface_show_alert_dialog(_("STR"),
			_("STR"
			"STR"),
			FALSE, NULL);
		return;
	}
	
	for (i = 0; i < selection_length (&screen.selectionInfo); i++){
		gerbv_selection_item_t sItem =
			selection_get_item_by_index (&screen.selectionInfo, i);

		gerbv_net_t *net = sItem.net;
		gerbv_image_t *image = sItem.image;

		if (net->interpolation == GERBV_INTERPOLATION_PAREA_START) {
			
			if (i != 0)
				g_message ("STR");

			g_message (_("STR"));
			parea_report (net, image, mainProject);
			net_layer_file_report (net, image, mainProject);
		} else {
			switch (net->aperture_state) {

			case GERBV_APERTURE_STATE_ON:
			case GERBV_APERTURE_STATE_FLASH:
				
				if (i != 0)
					g_message ("STR");
				break;

			default:
				break;
			}

			aperture_state_report (net, image, mainProject);
		}
	}
	
	g_message ("STR");
}