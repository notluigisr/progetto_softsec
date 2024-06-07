eap_authwithpeer(unit, localname)
int unit;
char *localname;
{
	eap_state *esp = &eap_states[unit];

	
	esp->es_client.ea_name = localname;
	esp->es_client.ea_namelen = strlen(localname);

	esp->es_client.ea_state = eapListen;

	
	if (esp->es_client.ea_timeout > 0)
		TIMEOUT(eap_client_timeout, (void *)esp,
		    esp->es_client.ea_timeout);
}