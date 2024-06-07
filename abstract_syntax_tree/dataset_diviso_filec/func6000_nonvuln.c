void CLASS romm_coeff (float romm_cam[3][3])
{
  static const float rgb_romm[3][3] =	
  { {  2.034193, -0.727420, -0.306766 },
    { -0.228811,  1.231729, -0.002922 },
    { -0.008565, -0.153273,  1.161839 } };
  int i, j, k;

  for (i=0; i < 3; i++)
    for (j=0; j < 3; j++)
      for (cmatrix[i][j] = k=0; k < 3; k++)
	cmatrix[i][j] += rgb_romm[i][k] * romm_cam[k][j];
#ifdef LIBRAW_LIBRARY_BUILD
  color_flags.cmatrix_state = LIBRAW_COLORSTATE_CALCULATED;
#endif
}