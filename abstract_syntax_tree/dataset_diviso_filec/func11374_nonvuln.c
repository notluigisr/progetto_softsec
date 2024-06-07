static int conf__parse_string(char **token, const char *name, char **value, char *saveptr)
{
	*token = strtok_r(NULL, "", &saveptr);
	if(*token){
		if(*value){
			log__printf(NULL, MOSQ_LOG_ERR, "STR", name);
			return MOSQ_ERR_INVAL;
		}
		
		while((*token)[0] == ' ' || (*token)[0] == '\t'){
			(*token)++;
		}
		if(mosquitto_validate_utf8(*token, strlen(*token))){
			log__printf(NULL, MOSQ_LOG_ERR, "STR");
			return MOSQ_ERR_INVAL;
		}
		*value = mosquitto__strdup(*token);
		if(!*value){
			log__printf(NULL, MOSQ_LOG_ERR, "STR");
			return MOSQ_ERR_NOMEM;
		}
	}else{
		log__printf(NULL, MOSQ_LOG_ERR, "STR", name);
		return MOSQ_ERR_INVAL;
	}
	return MOSQ_ERR_SUCCESS;
}