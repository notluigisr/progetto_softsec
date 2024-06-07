handle_initial_trim(void)
{
  double rate;
  long delta_time;
  double rtc_error_now, sys_error_now;

    
    
  run_regression(1, &coefs_valid, &coef_ref_time, &coef_seconds_fast, &coef_gain_rate);

  n_samples_since_regression = 0;

  

  n_samples = -1;


  read_coefs_from_file();

  if (valid_coefs_from_file) {
    
    delta_time = coef_ref_time - file_ref_time;
    rate = 1.0e-6 * file_rate_ppm;
    rtc_error_now = file_ref_offset + rate * (double) delta_time;
          
    
    sys_error_now = rtc_error_now - coef_seconds_fast;
          
    LCL_AccumulateOffset(sys_error_now, 0.0);
    LOG(LOGS_INFO, "STR",
        sys_error_now);
  } else {
    LOG(LOGS_WARN, "STR");
  }
  
  coefs_valid = 0;
  
  (after_init_hook)(after_init_hook_arg);
  
  operating_mode = OM_NORMAL;
}