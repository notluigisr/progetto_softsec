void Transform::interpolate_nearestneighbour( RawTile& in, unsigned int resampled_width, unsigned int resampled_height ){

  
  unsigned char *input = (unsigned char*) in.data;

  int channels = in.channels;
  unsigned int width = in.width;
  unsigned int height = in.height;

  
  unsigned char *output;

  
  bool new_buffer = false;
  if( resampled_width*resampled_height > in.width*in.height ){
    new_buffer = true;
    output = new unsigned char[(unsigned long long)resampled_width*resampled_height*in.channels];
  }
  else output = (unsigned char*) in.data;

  
  float xscale = (float)width / (float)resampled_width;
  float yscale = (float)height / (float)resampled_height;

  for( unsigned int j=0; j<resampled_height; j++ ){
    for( unsigned int i=0; i<resampled_width; i++ ){

      
      
      unsigned long ii = (unsigned int) floorf(i*xscale);
      unsigned long jj = (unsigned int) floorf(j*yscale);
      unsigned long pyramid_index = (unsigned int) channels * ( ii + jj*width );

      unsigned long long resampled_index = (unsigned long long)(i + j*resampled_width)*channels;
      for( int k=0; k<in.channels; k++ ){
	output[resampled_index+k] = input[pyramid_index+k];
      }
    }
  }

  
  if( new_buffer ) delete[] (unsigned char*) input;

  
  in.width = resampled_width;
  in.height = resampled_height;
  in.dataLength = resampled_width * resampled_height * channels * (in.bpc/8);
  in.data = output;
}