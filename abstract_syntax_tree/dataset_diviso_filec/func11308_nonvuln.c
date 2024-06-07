static void rdp_read_capability_set_header(wStream* s, UINT16* length, UINT16* type)
{
	Stream_Read_UINT16(s, *type);   
	Stream_Read_UINT16(s, *length); 
}