   This function runs the self test on the algorithm specified by the descriptor td */
PHP_FUNCTION(mcrypt_enc_self_test)
{
	MCRYPT_GET_TD_ARG
	RETURN_LONG(mcrypt_enc_self_test(pm->td));