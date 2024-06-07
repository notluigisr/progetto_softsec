 */
PHP_RSHUTDOWN_FUNCTION(imap)
{
	ERRORLIST *ecur = NIL;
	STRINGLIST *acur = NIL;

	if (IMAPG(imap_errorstack) != NIL) {
		
		if (EG(error_reporting) & E_NOTICE) {
			ecur = IMAPG(imap_errorstack);
			while (ecur != NIL) {
				php_error_docref(NULL, E_NOTICE, "STR", ecur->LTEXT, ecur->errflg);
				ecur = ecur->next;
			}
		}
		mail_free_errorlist(&IMAPG(imap_errorstack));
		IMAPG(imap_errorstack) = NIL;
	}

	if (IMAPG(imap_alertstack) != NIL) {
		
		if (EG(error_reporting) & E_NOTICE) {
			acur = IMAPG(imap_alertstack);
			while (acur != NIL) {
				php_error_docref(NULL, E_NOTICE, "STR", acur->LTEXT);
				acur = acur->next;
			}
		}
		mail_free_stringlist(&IMAPG(imap_alertstack));
		IMAPG(imap_alertstack) = NIL;
	}
	return SUCCESS;