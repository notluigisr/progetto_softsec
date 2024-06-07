void TileManager::crop( RawTile *ttt ){

  int tw = image->getTileWidth();
  int th = image->getTileHeight();

  if( loglevel >= 5 ){
    *logfile << "STR" << th
	     << "STR" << ttt->height
	     << endl;
  }

  
  
  int len = tw * th * ttt->channels * (ttt->bpc/8);
  unsigned char* buffer = (unsigned char*) malloc( len );
  unsigned char* src_ptr = (unsigned char*) memcpy( buffer, ttt->data, len );
  unsigned char* dst_ptr = (unsigned char*) ttt->data;

  
  len =  ttt->width * ttt->channels * (ttt->bpc/8);
  for( unsigned int i=0; i<ttt->height; i++ ){
    memcpy( dst_ptr, src_ptr, len );
    dst_ptr += len;
    src_ptr += tw * ttt->channels * (ttt->bpc/8);
  }

  free( buffer );

  
  len = ttt->width * ttt->height * ttt->channels * (ttt->bpc/8);
  ttt->dataLength = len;
  ttt->padded = false;

}