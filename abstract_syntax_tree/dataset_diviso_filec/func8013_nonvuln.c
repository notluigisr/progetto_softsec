uint32 Field_blob::char_length() const
{
  switch (packlength)
  {
  case 1:
    return 255;
  case 2:
    return 65535;
  case 3:
    return 16777215;
  case 4:
    return (uint32) 4294967295U;
  default:
    DBUG_ASSERT(0); 
    return 0;
  }
}