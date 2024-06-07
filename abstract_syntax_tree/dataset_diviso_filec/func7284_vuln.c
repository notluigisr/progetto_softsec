  write_header( FT_Error  error_code )
  {
    FT_Face      face;
    const char*  basename;


    error = FTC_Manager_LookupFace( handle->cache_manager,
                                    handle->scaler.face_id, &face );
    if ( error )
      PanicZ( "STR" );

    if ( !status.header )
    {
      basename = ft_basename( handle->current_font->filepathname );

      switch ( error_code )
      {
      case FT_Err_Ok:
        sprintf( status.header_buffer, "STR", face->family_name,
                 face->style_name, basename );
        break;
      case FT_Err_Invalid_Pixel_Size:
        sprintf( status.header_buffer, "STR",
                 basename );
        break;
      case FT_Err_Invalid_PPem:
        sprintf( status.header_buffer, "STR",
                 basename );
        break;
      default:
        sprintf( status.header_buffer, "STR", basename,
            (FT_UShort)error_code );
        break;
      }

      status.header = status.header_buffer;
    }

    grWriteCellString( display->bitmap, 0, 0,
                       status.header, display->fore_color );

    sprintf( status.header_buffer, "STR",
             status.ptsize/64.0, status.angle );
    grWriteCellString( display->bitmap, 0, CELLSTRING_HEIGHT,
                       status.header_buffer, display->fore_color );

    grRefreshSurface( display->surface );
  }