static int eval_if(const char *hdr, const char *etag, const char *lock_token,
		   unsigned *locked)
{
    unsigned ret = 0;
    tok_t tok_l;
    char *list;

    
    tok_init(&tok_l, hdr, "STR", TOK_TRIMLEFT|TOK_TRIMRIGHT);
    while ((list = tok_next(&tok_l))) {
	unsigned ret_l = 1;
	tok_t tok_c;
	char *cond;

	

	
	tok_initm(&tok_c, list+1, "STR", TOK_TRIMLEFT|TOK_TRIMRIGHT);
	while ((cond = tok_next(&tok_c))) {
	    unsigned r, not = 0;

	    if (!strncmp(cond, "STR", 3)) {
		not = 1;
		cond += 3;
		while (*cond == ' ') cond++;
	    }
	    if (*cond == '[') {
		
		r = !etagcmp(cond+1, etag);
	    }
	    else {
		
		if (!lock_token) r = 0;
		else {
		    r = !strcmp(cond+1, lock_token);
		    if (r) {
			
			*locked = 0;
		    }
		}
	    }

	    ret_l &= (not ? !r : r);
	}

	tok_fini(&tok_c);

	ret |= ret_l;
    }

    tok_fini(&tok_l);

    return (ret || locked);
}