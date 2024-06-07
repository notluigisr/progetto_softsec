const uchar *Field_blob::unpack(uchar *to, const uchar *from,
                                const uchar *from_end, uint param_data)
{
  DBUG_ENTER("STR");
  DBUG_PRINT("STR",
                       to, from, param_data));
  uint const master_packlength=
    param_data > 0 ? param_data & 0xFF : packlength;
  if (from + master_packlength > from_end)
    DBUG_RETURN(0);                             
  uint32 const length= get_length(from, master_packlength);
  DBUG_DUMP("STR", from, length + master_packlength);
  bitmap_set_bit(table->write_set, field_index);
  if (from + master_packlength + length > from_end)
    DBUG_RETURN(0);
  store(reinterpret_cast<const char*>(from) + master_packlength,
        length, field_charset);
  DBUG_DUMP("STR", to, table->s->reclength);
  DBUG_RETURN(from + master_packlength + length);
}