int my_vio_is_encrypted(MYSQL_PLUGIN_VIO *vio)
{
  MPVIO_EXT *mpvio= (MPVIO_EXT *) vio;
  return (mpvio->vio_is_encrypted);
}