int DoTransform(cmsHTRANSFORM hXForm, int OutputColorSpace)
{
    JSAMPROW ScanLineIn;
    JSAMPROW ScanLineOut;


       
       
       Compressor.density_unit = Decompressor.density_unit;
       Compressor.X_density    = Decompressor.X_density;
       Compressor.Y_density    = Decompressor.Y_density;

      

       jpeg_start_decompress(&Decompressor);
       jpeg_start_compress(&Compressor, TRUE);

        if (OutputColorSpace == PT_Lab)
            SetITUFax(&Compressor);

       
       if (EmbedProfile && cOutProf)
           DoEmbedProfile(cOutProf);

       ScanLineIn  = (JSAMPROW) malloc(Decompressor.output_width * Decompressor.num_components);
       ScanLineOut = (JSAMPROW) malloc(Compressor.image_width * Compressor.num_components);

       while (Decompressor.output_scanline <
                            Decompressor.output_height) {

       jpeg_read_scanlines(&Decompressor, &ScanLineIn, 1);

       cmsDoTransform(hXForm, ScanLineIn, ScanLineOut, Decompressor.output_width);

       jpeg_write_scanlines(&Compressor, &ScanLineOut, 1);
       }

       free(ScanLineIn);
       free(ScanLineOut);

       jpeg_finish_decompress(&Decompressor);
       jpeg_finish_compress(&Compressor);

       return TRUE;
}