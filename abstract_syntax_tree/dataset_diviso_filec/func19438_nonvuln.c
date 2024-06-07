drv_screen_init(SCREEN *sp)
{
    TERMINAL_CONTROL_BLOCK *TCB = TCBOf(sp);

    AssertTCB();

    
    sp->_use_rmso = SGR0_TEST(exit_standout_mode);
    sp->_use_rmul = SGR0_TEST(exit_underline_mode);

    
    sp->_scrolling = ((scroll_forward && scroll_reverse) ||
		      ((parm_rindex ||
			parm_insert_line ||
			insert_line) &&
		       (parm_index ||
			parm_delete_line ||
			delete_line)));

    NCURSES_SP_NAME(baudrate) (sp);

    NCURSES_SP_NAME(_nc_mvcur_init) (sp);
    
    NCURSES_SP_NAME(_nc_screen_init) (sp);
}