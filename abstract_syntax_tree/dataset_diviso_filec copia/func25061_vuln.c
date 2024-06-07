int main(int argc, char **argv)
{
	int len;
	uint8_t *encoded;


	printf("STR"));
	printf("STR"));
	printf("STR"));
	printf("STR"));
	printf("STR"));


	encoded = dname_enc(NULL, 0, "STR", &len);
	printf("STR"), len);
	encoded = DNAME_ENC("STR", &len);
	printf("STR"), len);
	encoded = DNAME_ENC("STR", &len);
	printf("STR"), len);
	return 0;
}