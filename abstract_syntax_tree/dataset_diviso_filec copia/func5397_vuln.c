  write_header( FT_Error error_code )
  {
    FT_Face      face;
    const char*  basename;
    const char*  format;


    error = FTC_Manager_LookupFace( handle->cache_manager,
                                    handle->scaler.face_id, &face );
    if ( error )
      Fatal( "STR" );

    if ( !status.header )
    {
      basename = ft_basename( handle->current_font->filepathname );

      switch ( error_code )
      {
      case FT_Err_Ok:
        sprintf( status.header_buffer, "STR",
                 face->family_name, face->style_name, basename );
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
        sprintf( status.header_buffer, "STR",
                 basename, (FT_UShort)error_code );
        break;
      }

      status.header = (const char *)status.header_buffer;
    }

    grWriteCellString( display->bitmap, 0, 0, status.header,
                       display->fore_color );

    format = "STR";

    snprintf( status.header_buffer, 256, format, status.ptsize/64., status.Num );

    if ( FT_HAS_GLYPH_NAMES( face ) )
    {
      char*  p;
      int    format_len, gindex, size;


      size = strlen( status.header_buffer );
      p    = status.header_buffer + size;
      size = 256 - size;

      format = "STR";
      format_len = strlen( format );

      if ( size >= format_len + 2 )
      {
        gindex = status.Num;

        strcpy( p, format );
        if ( FT_Get_Glyph_Name( face, gindex, p + format_len, size - format_len ) )
          *p = '\0';
      }
    }

    status.header = (const char *)status.header_buffer;
    grWriteCellString( display->bitmap, 0, HEADER_HEIGHT,
                       status.header_buffer, display->fore_color );

    grRefreshSurface( display->surface );
  }