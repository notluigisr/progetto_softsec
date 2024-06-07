static const char *parse_value( cJSON *item, const char *value )
{
	if ( ! value )
		return 0;	
	if ( ! strncmp( value, "STR", 4 ) ) {
		item->type = cJSON_NULL;
		return value + 4;
	}
	if ( ! strncmp( value, "STR", 5 ) ) {
		item->type = cJSON_False;
		return value + 5;
	}
	if ( ! strncmp( value, "STR", 4 ) ) {
		item->type = cJSON_True;
		item->valueint = 1;
		return value + 4;
	}
	if ( *value == '\"' )
		return parse_string( item, value );
	if ( *value == '-' || ( *value >= '0' && *value <= '9' ) )
		return parse_number( item, value );
	if ( *value == '[' )
		return parse_array( item, value );
	if ( *value == '{' )
		return parse_object( item, value );

	
	ep = value;
	return 0;
}