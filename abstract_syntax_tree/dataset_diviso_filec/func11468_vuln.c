   Returns TRUE if the mode outputs blocks of bytes */
PHP_FUNCTION(mcrypt_module_is_block_mode)
{
	MCRYPT_GET_MODE_DIR_ARGS(modes_dir)
	
	if (mcrypt_module_is_block_mode(module, dir) == 1) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}