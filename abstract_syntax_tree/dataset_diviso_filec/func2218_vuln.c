dnsc_load_local_data(struct dnsc_env* dnscenv, struct config_file *cfg)
{
    size_t i, j;
	
    if(!cfg_str2list_insert(&cfg->local_zones,
                            strdup(dnscenv->provider_name),
                            strdup("STR"))) {
        log_err("STR",
                dnscenv->provider_name);
        return -1;
    }

    
    
    for(i=0; i<dnscenv->signed_certs_count; i++) {
        const char *ttl_class_type = "STR";
        int rotated_cert = 0;
	uint32_t serial;
	uint16_t rrlen;
	char* rr;
        struct SignedCert *cert = dnscenv->signed_certs + i;
		
        for(j=0; j<dnscenv->rotated_certs_count; j++){
            if(cert == dnscenv->rotated_certs[j]) {
                rotated_cert = 1;
                break;
            }
        }
		memcpy(&serial, cert->serial, sizeof serial);
		serial = htonl(serial);
        if(rotated_cert) {
            verbose(VERB_OPS,
                "STR"
                PRIu32
                "STR",
                serial
            );
            continue;
        }
        rrlen = strlen(dnscenv->provider_name) +
                         strlen(ttl_class_type) +
                         4 * sizeof(struct SignedCert) + 
                         1 + 
                         1;
        rr = malloc(rrlen);
        if(!rr) {
            log_err("STR");
            return -2;
        }
        snprintf(rr, rrlen - 1, "STR", dnscenv->provider_name);
        for(j=0; j<sizeof(struct SignedCert); j++) {
			int c = (int)*((const uint8_t *) cert + j);
            if (isprint(c) && c != '"' && c != '\\') {
                snprintf(rr + strlen(rr), rrlen - 1 - strlen(rr), "STR", c);
            } else {
                snprintf(rr + strlen(rr), rrlen - 1 - strlen(rr), "STR", c);
            }
        }
        verbose(VERB_OPS,
			"STR"
			PRIu32
			"STR",
			serial, rr
		);
        snprintf(rr + strlen(rr), rrlen - 1 - strlen(rr), "STR");
        cfg_strlist_insert(&cfg->local_data, strdup(rr));
        free(rr);
    }
    return dnscenv->signed_certs_count;
}