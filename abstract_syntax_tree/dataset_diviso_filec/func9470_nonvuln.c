void Transform::shade( RawTile& in, int h_angle, int v_angle ){

  float o_x, o_y, o_z;

  
  float a = (h_angle * 2 * M_PI) / 360.0;

  
  float s_y = cos(a);
  float s_x = sqrt( 1.0 - s_y*s_y );
  if( h_angle > 180 ){
    s_x = -s_x;
  }

  a = (v_angle * 2 * M_PI) / 360.0;
  float s_z = - sin(a);

  float s_norm = sqrt( s_x*s_x + s_y*s_y + s_z*s_z );
  s_x = s_x / s_norm;
  s_y = s_y / s_norm;
  s_z = s_z / s_norm;

  float *buffer, *infptr;

  unsigned int ndata = in.dataLength * 8 / in.bpc;

  infptr= (float*)in.data;

  
  buffer = new float[ndata];


#if defined(__ICC) || defined(__INTEL_COMPILER)
#pragma ivdep
#elif defined(_OPENMP)
#pragma omp parallel for
#endif
  for( unsigned int k=0; k<ndata; k++ ){

    unsigned int n = k*3;
    if( infptr[n] == 0.0 && infptr[n+1] == 0.0 && infptr[n+2] == 0.0 ){
      o_x = o_y = o_z = 0.0;
    }
    else {
      o_x = (float) - ((float)infptr[n]-0.5) * 2.0;
      o_y = (float) - ((float)infptr[n+1]-0.5) * 2.0;
      o_z = (float) - ((float)infptr[n+2]-0.5) * 2.0;
    }

    float dot_product;
    dot_product = (s_x*o_x) + (s_y*o_y) + (s_z*o_z);

    dot_product = 0.5 * dot_product;
    if( dot_product < 0.0 ) dot_product = 0.0;
    if( dot_product > 1.0 ) dot_product = 1.0;

    buffer[k] = dot_product;
  }


  
  delete[] (float*) in.data;

  in.data = buffer;
  in.channels = 1;
  in.dataLength = in.width * in.height * (in.bpc/8);
}