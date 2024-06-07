uchar *Field_string::pack(uchar *to, const uchar *from, uint max_length)
{
  uint length=      MY_MIN(field_length,max_length);
  uint local_char_length= max_length/field_charset->mbmaxlen;
  DBUG_PRINT("STR", field_name, length));

  if (length > local_char_length)
    local_char_length= my_charpos(field_charset, from, from+length,
                                  local_char_length);
  set_if_smaller(length, local_char_length);
 
  
  if (field_charset->mbmaxlen == 1)
  {
    while (length && from[length-1] == field_charset->pad_char)
      length --;
  }
  else
    length= field_charset->cset->lengthsp(field_charset, (const char*) from, length);

  
  *to++= (uchar) length;
  if (field_length > 255)
    *to++= (uchar) (length >> 8);

  
  memcpy(to, from, length);
  return to+length;
}