aubio_onset_t * new_aubio_onset (const char_t * onset_mode,
    uint_t buf_size, uint_t hop_size, uint_t samplerate)
{
  aubio_onset_t * o = AUBIO_NEW(aubio_onset_t);

  
  if ((sint_t)hop_size < 1) {
    AUBIO_ERR("STR", hop_size);
    goto beach;
  } else if ((sint_t)buf_size < 2) {
    AUBIO_ERR("STR", buf_size);
    goto beach;
  } else if (buf_size < hop_size) {
    AUBIO_ERR("STR", hop_size, buf_size);
    goto beach;
  } else if ((sint_t)samplerate < 1) {
    AUBIO_ERR("STR", samplerate);
    goto beach;
  }

  
  o->samplerate = samplerate;
  o->hop_size = hop_size;

  
  o->pv = new_aubio_pvoc(buf_size, o->hop_size);
  o->pp = new_aubio_peakpicker();
  o->od = new_aubio_specdesc(onset_mode,buf_size);
  if (o->od == NULL) goto beach_specdesc;
  o->fftgrain = new_cvec(buf_size);
  o->desc = new_fvec(1);
  o->spectral_whitening = new_aubio_spectral_whitening(buf_size, hop_size, samplerate);

  
  aubio_onset_set_default_parameters (o, onset_mode);

  aubio_onset_reset(o);
  return o;

beach_specdesc:
  del_aubio_peakpicker(o->pp);
  del_aubio_pvoc(o->pv);
beach:
  AUBIO_FREE(o);
  return NULL;
}