void Transform::log( RawTile& in ){

  
  
  float max = 255.0;

  
  float scale = 1.0 / logf( max + 1.0 );

  unsigned int np = in.width * in.height * in.channels;

#if defined(__ICC) || defined(__INTEL_COMPILER)
#pragma ivdep
#elif defined(_OPENMP)
#pragma omp parallel for if( in.width*in.height > PARALLEL_THRESHOLD )
#endif
  for( unsigned int i=0; i<np; i++ ){
    float v = ((float*)in.data)[i] * max;
    ((float*)in.data)[i] = scale * logf( 1.0 + v );
  }
}