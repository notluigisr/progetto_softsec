dwg_errstrings (int error)
{
  if (error & 1)
    HANDLER (OUTPUT, "STR");
  if (error & 2)
    HANDLER (OUTPUT, "STR");
  if (error & 4)
    HANDLER (OUTPUT, "STR");
  if (error & 8)
    HANDLER (OUTPUT, "STR");
  if (error & 16)
    HANDLER (OUTPUT, "STR");
  if (error & 32)
    HANDLER (OUTPUT, "STR");
  if (error & 64)
    HANDLER (OUTPUT, "STR");
  
  if (error > 127)
    HANDLER (OUTPUT, "STR");
  if (error & 128)
    HANDLER (OUTPUT, "STR");
  if (error & 256)
    HANDLER (OUTPUT, "STR");
  if (error & 512)
    HANDLER (OUTPUT, "STR");
  if (error & 1024)
    HANDLER (OUTPUT, "STR");
  if (error & 2048)
    HANDLER (OUTPUT, "STR");
  if (error & 4096)
    HANDLER (OUTPUT, "STR");
  if (error & 8192)
    HANDLER (OUTPUT, "STR");
  HANDLER (OUTPUT, "STR");
}