cJSON *cJSON_CreateFloat( double num )
{
	cJSON *item = cJSON_New_Item();
	if ( item ) {
		item->type = cJSON_Number;
		item->valuefloat = num;
		item->valueint = num;
	}
	return item;
}