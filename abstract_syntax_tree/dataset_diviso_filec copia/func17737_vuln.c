aubio_tempo_t * new_aubio_tempo (const char_t * tempo_mode,
    uint_t buf_size, uint_t hop_size, uint_t samplerate)
{
  aubio_tempo_t * o = AUBIO_NEW(aubio_tempo_t);
  char_t specdesc_func[20];
  o->samplerate = samplerate;
  
  if ((sint_t)hop_size < 1) {
    AUBIO_ERR("STR", hop_size);
    goto beach;
  } else if ((sint_t)buf_size < 2) {
    AUBIO_ERR("STR", buf_size);
    goto beach;
  } else if (buf_size < hop_size) {
    AUBIO_ERR("STR", buf_size, hop_size);
    goto beach;
  } else if ((sint_t)samplerate < 1) {
    AUBIO_ERR("STR", samplerate);
    goto beach;
  }

  
  o->winlen = aubio_next_power_of_two(5.8 * samplerate / hop_size);
  if (o->winlen < 4) o->winlen = 4;
  o->step = o->winlen/4;
  o->blockpos = 0;
  o->threshold = 0.3;
  o->silence = -90.;
  o->total_frames = 0;
  o->last_beat = 0;
  o->delay = 0;
  o->hop_size = hop_size;
  o->dfframe  = new_fvec(o->winlen);
  o->fftgrain = new_cvec(buf_size);
  o->out      = new_fvec(o->step);
  o->pv       = new_aubio_pvoc(buf_size, hop_size);
  o->pp       = new_aubio_peakpicker();
  aubio_peakpicker_set_threshold (o->pp, o->threshold);
  if ( strcmp(tempo_mode, "STR") == 0 ) {
    strcpy(specdesc_func, "STR");
  } else {
    strcpy(specdesc_func, tempo_mode);
  }
  o->od       = new_aubio_specdesc(specdesc_func,buf_size);
  o->of       = new_fvec(1);
  o->bt       = new_aubio_beattracking(o->winlen, o->hop_size, o->samplerate);
  o->onset    = new_fvec(1);
  
  o->last_tatum = 0;
  o->tatum_signature = 4;
  return o;

beach:
  AUBIO_FREE(o);
  return NULL;
}