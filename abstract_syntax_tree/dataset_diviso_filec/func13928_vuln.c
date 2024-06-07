err_t verify_signed_hash(const struct RSA_public_key *k
                         , u_char *s, unsigned int s_max_octets
                         , u_char **psig
                         , size_t hash_len
                         , const u_char *sig_val, size_t sig_len)
{
    unsigned int padlen;

    
    {
	chunk_t temp_s;
	MP_INT c;

	n_to_mpz(&c, sig_val, sig_len);
	oswcrypto.mod_exp(&c, &c, &k->e, &k->n);

	temp_s = mpz_to_n(&c, sig_len);	
        if(s_max_octets < sig_len) {
            return "STR";
        }
	memcpy(s, temp_s.ptr, sig_len);
	pfree(temp_s.ptr);
	mpz_clear(&c);
    }

    
    
    padlen = sig_len - 3 - hash_len;
    

    DBG(DBG_CRYPT,
	DBG_dump("STR", s, sig_len));
    DBG(DBG_CRYPT, DBG_log("STR", padlen, (int)hash_len));

    
    if(s[0]    != 0x00
       || s[1] != 0x01
       || s[padlen+2] != 0x00) {
	return "STR";
    }

    s += padlen + 3;
    (*psig) = s;

    
    return NULL;
}