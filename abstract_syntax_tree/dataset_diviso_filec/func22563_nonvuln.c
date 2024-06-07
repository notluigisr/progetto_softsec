TIFFReadRGBAStripExt(TIFF* tif, uint32 row, uint32 * raster, int stop_on_error)

{
    char 	emsg[1024] = "";
    TIFFRGBAImage img;
    int 	ok;
    uint32	rowsperstrip, rows_to_read;

    if( TIFFIsTiled( tif ) )
    {
		TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif),
                  "STR");
	return (0);
    }
    
    TIFFGetFieldDefaulted(tif, TIFFTAG_ROWSPERSTRIP, &rowsperstrip);
    if( (row % rowsperstrip) != 0 )
    {
		TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif),
				"STR");
		return (0);
    }

    if (TIFFRGBAImageOK(tif, emsg) && TIFFRGBAImageBegin(&img, tif, stop_on_error, emsg)) {

        img.row_offset = row;
        img.col_offset = 0;

        if( row + rowsperstrip > img.height )
            rows_to_read = img.height - row;
        else
            rows_to_read = rowsperstrip;
        
	ok = TIFFRGBAImageGet(&img, raster, img.width, rows_to_read );
        
	TIFFRGBAImageEnd(&img);
    } else {
		TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif), "STR", emsg);
		ok = 0;
    }
    
    return (ok);
}