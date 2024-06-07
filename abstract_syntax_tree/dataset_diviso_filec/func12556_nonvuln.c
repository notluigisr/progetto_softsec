int ReadTile(TIFF* tiff, UINT32 col, UINT32 row, UINT32* buffer) {
    uint16 photometric;

    TIFFGetField(tiff, TIFFTAG_PHOTOMETRIC, &photometric);

    
    if (photometric == PHOTOMETRIC_YCBCR) {
        UINT32 tile_width, tile_height, swap_line_size, i_row;
        UINT32* swap_line;

        TIFFGetField(tiff, TIFFTAG_TILEWIDTH, &tile_width);
        TIFFGetField(tiff, TIFFTAG_TILELENGTH, &tile_height);

        swap_line_size = tile_width * sizeof(UINT32);
        if (tile_width != swap_line_size / sizeof(UINT32)) {
            return -1;
        }

        
        if (!TIFFReadRGBATile(tiff, col, row, buffer)) {
            return -1;
        }

        swap_line = (UINT32*)malloc(swap_line_size);
        if (swap_line == NULL) {
            return -1;
        }
        
        for(i_row = 0; i_row < tile_height / 2; i_row++) {
            UINT32 *top_line, *bottom_line;

            top_line = buffer + tile_width * i_row;
            bottom_line = buffer + tile_width * (tile_height - i_row - 1);

            memcpy(swap_line, top_line, 4*tile_width);
            memcpy(top_line, bottom_line, 4*tile_width);
            memcpy(bottom_line, swap_line, 4*tile_width);
        }

        free(swap_line);

        return 0;
    }

    if (TIFFReadTile(tiff, (tdata_t)buffer, col, row, 0, 0) == -1) {
        TRACE(("STR", col, row));
        return -1;
    }

    TRACE(("STR", col, row));

    return 0;
}