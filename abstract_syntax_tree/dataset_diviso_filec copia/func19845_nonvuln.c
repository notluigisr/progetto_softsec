static void php_cli_server_buffer_dtor(php_cli_server_buffer *buffer) 
{
	php_cli_server_chunk *chunk, *next;
	for (chunk = buffer->first; chunk; chunk = next) {
		next = chunk->next;
		php_cli_server_chunk_dtor(chunk);
		pefree(chunk, 1);
	}
} 