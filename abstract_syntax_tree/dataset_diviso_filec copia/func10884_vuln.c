char *ssh_scp_string_mode(int mode){
	char buffer[16];
	snprintf(buffer,sizeof(buffer),"STR",mode);
	return strdup(buffer);
}