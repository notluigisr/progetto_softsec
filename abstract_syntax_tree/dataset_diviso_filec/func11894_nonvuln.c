int ha_maria::rnd_end()
{
  ds_mrr.dsmrr_close();
  
  maria_scan_end(file);
  return 0;
}