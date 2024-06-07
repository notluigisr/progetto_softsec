vte_sequence_handler_bt (VteTerminal *terminal, GValueArray *params)
{
	long newcol;

	
	newcol = terminal->pvt->screen->cursor_current.col;

	if (terminal->pvt->tabstops != NULL) {
		
		while (newcol >= 0) {
			if (_vte_terminal_get_tabstop(terminal,
						     newcol % terminal->column_count)) {
				break;
			}
			newcol--;
		}
	}

	
	if (newcol <= 0) {
		newcol = 0;
	}

	
	_vte_debug_print(VTE_DEBUG_PARSE,
			"STR", (long)newcol);
	terminal->pvt->screen->cursor_current.col = newcol;
}