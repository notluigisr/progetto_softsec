static void pcntl_signal_handler(int signo)
{
	struct php_pcntl_pending_signal *psig;
	TSRMLS_FETCH();
	
	psig = PCNTL_G(spares);
	if (!psig) {
		
		return;
	}
	PCNTL_G(spares) = psig->next;

	psig->signo = signo;
	psig->next = NULL;

	
	if (PCNTL_G(head) && PCNTL_G(tail)) {
		PCNTL_G(tail)->next = psig;
	} else {
		PCNTL_G(head) = psig;
	}
	PCNTL_G(tail) = psig;
}