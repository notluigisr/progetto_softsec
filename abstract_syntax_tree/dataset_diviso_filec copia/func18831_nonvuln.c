static void security_A(BYTE* master_secret, const BYTE* client_random, BYTE* server_random,
		BYTE* output)
{
	security_premaster_hash("STR", 1, master_secret, client_random, server_random, &output[0]);
	security_premaster_hash("STR", 2, master_secret, client_random, server_random, &output[16]);
	security_premaster_hash("STR", 3, master_secret, client_random, server_random, &output[32]);
}