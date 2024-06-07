sldns_parse_rdf_token(sldns_buffer* strbuf, char* token, size_t token_len,
	int* quoted, int* parens, size_t* pre_data_pos,
	const char* delimiters, sldns_rdf_type rdftype, size_t* token_strlen)
{
	size_t slen;

	
	while(sldns_buffer_remaining(strbuf) > 0 && !*quoted &&
		*(sldns_buffer_current(strbuf)) == ' ') {
		sldns_buffer_skip(strbuf, 1);
	}

	*pre_data_pos = sldns_buffer_position(strbuf);
	if(sldns_bget_token_par(strbuf, token, (*quoted)?"STR":delimiters,
		token_len, parens, (*quoted)?NULL:"STR") == -1) {
		return 0;
	}
	slen = strlen(token);
	
	if(!*quoted && sldns_rdf_type_maybe_quoted(rdftype) &&
		slen >= 2 &&
		(token[0] == '"' || token[0] == '\'') && 
		(token[slen-1] == '"' || token[slen-1] == '\'')) {
		
		memmove(token, token+1, slen-2);
		token[slen-2] = 0;
		slen -= 2;
		*quoted = 1;
	} else if(!*quoted && sldns_rdf_type_maybe_quoted(rdftype) &&
		slen >= 2 &&
		(token[0] == '"' || token[0] == '\'')) {
		
		memmove(token, token+1, slen-1);
		token[slen-1] = 0;
		slen -= 1;
		*quoted = 1;
		
		while(sldns_buffer_position(strbuf) > 0 &&
			(sldns_buffer_current(strbuf)[-1] == ' ' ||
			sldns_buffer_current(strbuf)[-1] == '\t')) {
			sldns_buffer_skip(strbuf, -1);
		}
		if(sldns_bget_token_par(strbuf, token+slen,
			"STR", token_len-slen,
			parens, NULL) == -1) {
			return 0;
		}
		slen = strlen(token);
	}
	*token_strlen = slen;
	return 1;
}