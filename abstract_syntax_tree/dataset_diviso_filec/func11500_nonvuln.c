TIFFReadRGBATile(TIFF* tif, uint32 col, uint32 row, uint32 * raster)

{
    return TIFFReadRGBATileExt(tif, col, row, raster, 0 );
}