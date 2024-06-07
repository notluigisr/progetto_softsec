Field_blob::Field_blob(uchar *ptr_arg, uchar *null_ptr_arg, uchar null_bit_arg,
		       enum utype unireg_check_arg,
                       const LEX_CSTRING *field_name_arg,
                       TABLE_SHARE *share, uint blob_pack_length,
		       const DTCollation &collation)
  :Field_longstr(ptr_arg, BLOB_PACK_LENGTH_TO_MAX_LENGH(blob_pack_length),
                 null_ptr_arg, null_bit_arg, unireg_check_arg, field_name_arg,
                 collation),
   packlength(blob_pack_length)
{
  DBUG_ASSERT(blob_pack_length <= 4); 
  flags|= BLOB_FLAG;
  share->blob_fields++;
  
}