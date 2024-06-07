   Returns TRUE if the mode is for use with block algorithms */
PHP_FUNCTION(mcrypt_module_is_block_algorithm_mode)
{
	MCRYPT_GET_MODE_DIR_ARGS(modes_dir)
	
	if (mcrypt_module_is_block_algorithm_mode(module, dir) == 1) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}