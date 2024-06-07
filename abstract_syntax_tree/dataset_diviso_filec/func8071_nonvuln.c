String *Item_func_aes_decrypt::val_str(String *str)
{
  DBUG_ASSERT(fixed == 1);
  char key_buff[80];
  String tmp_key_value(key_buff, sizeof(key_buff), system_charset_info);
  String *sptr, *key;
  THD *thd= current_thd;
  ulong aes_opmode;
  iv_argument iv_arg;
  DBUG_ENTER("STR");

  sptr= args[0]->val_str(str);			
  key=  args[1]->val_str(&tmp_key_value);	
  aes_opmode= thd->variables.my_aes_mode;
  DBUG_ASSERT(aes_opmode <= MY_AES_END);

  if (sptr && key)  			
  {
    const unsigned char *iv_str=
      iv_arg.retrieve_iv_ptr((enum my_aes_opmode) aes_opmode, arg_count, args,
      func_name(), thd, &null_value);
    if (null_value)
      DBUG_RETURN(NULL);
    str_value.set_charset(&my_charset_bin);
    if (!str_value.alloc(sptr->length()))  
    {
      
      int length;
      length= my_aes_decrypt((unsigned char *) sptr->ptr(), sptr->length(),
                             (unsigned char *) str_value.ptr(),
                             (unsigned char *) key->ptr(), key->length(),
                             (enum my_aes_opmode) aes_opmode, iv_str);
      if (length >= 0)  
      {
        str_value.length((uint) length);
        DBUG_RETURN(&str_value);
      }
    }
  }
  
  null_value=1;
  DBUG_RETURN(0);
}