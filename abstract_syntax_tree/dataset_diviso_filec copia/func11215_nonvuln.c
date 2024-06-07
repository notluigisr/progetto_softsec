sound_beep (session *sess)
{
	if (!prefs.hex_gui_focus_omitalerts || fe_gui_info (sess, 0) != 1)
	{
		if (sound_files[XP_TE_BEEP] && sound_files[XP_TE_BEEP][0])
			
			sound_play_event (XP_TE_BEEP);
		else
			
			fe_beep (sess);
	}
}