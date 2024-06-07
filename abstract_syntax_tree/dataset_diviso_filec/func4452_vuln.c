postprocess_terminfo(TERMTYPE2 *tp)
{
    

    
    if (PRESENT(box_chars_1)) {
	char buf2[MAX_TERMCAP_LENGTH];
	string_desc result;

	_nc_str_init(&result, buf2, sizeof(buf2));
	_nc_safe_strcat(&result, acs_chars);

	append_acs0(&result, 'l', box_chars_1[0]);	
	append_acs0(&result, 'q', box_chars_1[1]);	
	append_acs0(&result, 'k', box_chars_1[2]);	
	append_acs0(&result, 'x', box_chars_1[3]);	
	append_acs0(&result, 'j', box_chars_1[4]);	
	append_acs0(&result, 'm', box_chars_1[5]);	
	append_acs0(&result, 'w', box_chars_1[6]);	
	append_acs0(&result, 'u', box_chars_1[7]);	
	append_acs0(&result, 'v', box_chars_1[8]);	
	append_acs0(&result, 't', box_chars_1[9]);	
	append_acs0(&result, 'n', box_chars_1[10]);	

	if (buf2[0]) {
	    acs_chars = _nc_save_str(buf2);
	    _nc_warning("STR");
	    box_chars_1 = ABSENT_STRING;
	}
    }
    
}