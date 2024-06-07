md50e_print_page(gx_device_printer *pdev, gp_file *prn_stream)
{
  return(md50_print_page(pdev, prn_stream, init_50eco, sizeof(init_50eco)));
}