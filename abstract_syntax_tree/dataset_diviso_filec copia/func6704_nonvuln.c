static void set_mode(struct vc_data *vc, int on_off)
{
	int i;

	for (i = 0; i <= vc->vc_npar; i++)
		if (vc->vc_priv == EPdec) {
			switch(vc->vc_par[i]) {	
			case 1:			
				if (on_off)
					set_kbd(vc, decckm);
				else
					clr_kbd(vc, decckm);
				break;
			case 3:	
#if 0
				vc_resize(deccolm ? 132 : 80, vc->vc_rows);
				
#endif
				break;
			case 5:			
				if (vc->vc_decscnm != on_off) {
					vc->vc_decscnm = on_off;
					invert_screen(vc, 0, vc->vc_screenbuf_size, 0);
					update_attr(vc);
				}
				break;
			case 6:			
				vc->vc_decom = on_off;
				gotoxay(vc, 0, 0);
				break;
			case 7:			
				vc->vc_decawm = on_off;
				break;
			case 8:			
				if (on_off)
					set_kbd(vc, decarm);
				else
					clr_kbd(vc, decarm);
				break;
			case 9:
				vc->vc_report_mouse = on_off ? 1 : 0;
				break;
			case 25:		
				vc->vc_deccm = on_off;
				break;
			case 1000:
				vc->vc_report_mouse = on_off ? 2 : 0;
				break;
			}
		} else {
			switch(vc->vc_par[i]) {	
			case 3:			
				vc->vc_disp_ctrl = on_off;
				break;
			case 4:			
				vc->vc_decim = on_off;
				break;
			case 20:		
				if (on_off)
					set_kbd(vc, lnm);
				else
					clr_kbd(vc, lnm);
				break;
			}
		}
}