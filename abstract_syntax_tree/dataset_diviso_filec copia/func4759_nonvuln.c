write_uint32 (Header *header, guint8 *ptr, guint32 val)
{
  if (header->big_endian)
    *(guint32 *) ptr = GUINT32_TO_BE (val);
  else
    *(guint32 *) ptr = GUINT32_TO_LE (val);
}