cif_print_page(gx_device_printer *pdev, gp_file *prn_stream)
{	int line_size = gdev_mem_bytes_per_scan_line((gx_device *)pdev);
        int lnum;
        byte *in = (byte *)gs_malloc(pdev->memory, line_size, 1, "STR");
        char *s;
        int scanline, scanbyte;
        int length, start; 
                           

        if (in == 0)
                return_error(gs_error_VMerror);

        if ((s = strchr(pdev->fname, '.')) == NULL)
                length = strlen(pdev->fname) + 1;
        else
                length = s - pdev->fname;
        s = (char *)gs_malloc(pdev->memory, length, sizeof(char), "STR");

        strncpy(s, pdev->fname, length);
        *(s + length) = '\0';
        gp_fprintf(prn_stream, "STR", s);
        gs_free(pdev->memory, s, length, 1, "STR");

   for (lnum = 0; lnum < pdev->height; lnum++) {
      gdev_prn_copy_scan_lines(pdev, lnum, in, line_size);
      length = 0;
      for (scanline = 0; scanline < line_size; scanline++)
#ifdef TILE			
         for (scanbyte = 0; scanbyte < 8; scanbyte++)
            if (((in[scanline] >> scanbyte) & 1) != 0)
               gp_fprintf(prn_stream, "STR",
                  (scanline * 8 + (7 - scanbyte)) * 4,
                  (pdev->height - lnum) * 4);
#else				
         for (scanbyte = 7; scanbyte >= 0; scanbyte--)
            
            if (((in[scanline] >> scanbyte) & 1) != 0) {
               if (length == 0)
                  start = (scanline * 8 + (7 - scanbyte));
               length++;
            } else {
               if (length != 0)
                  gp_fprintf(prn_stream, "STR", length * 4,
                           start * 4 + length * 2,
                           (pdev->height - lnum) * 4);
               length = 0;
            }
#endif
   }
        gp_fprintf(prn_stream, "STR");
        gs_free(pdev->memory, in, line_size, 1, "STR");
        return 0;
}