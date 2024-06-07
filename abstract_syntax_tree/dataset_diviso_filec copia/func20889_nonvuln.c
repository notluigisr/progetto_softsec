static int get_result_width(MYSQL_RES *result)
{
  unsigned int len= 0;
  MYSQL_FIELD *field;
  MYSQL_FIELD_OFFSET offset;
  
#ifndef DBUG_OFF
  offset= mysql_field_tell(result);
  DBUG_ASSERT(offset == 0);
#else
  offset= 0;
#endif

  while ((field= mysql_fetch_field(result)) != NULL)
    len+= get_field_disp_length(field) + 3; 

  (void) mysql_field_seek(result, offset);	

  return len + 1; 
}