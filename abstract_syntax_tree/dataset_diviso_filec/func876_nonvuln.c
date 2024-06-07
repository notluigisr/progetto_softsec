void PSOutputDev::type3D1(GfxState *state, double wx, double wy,
			  double llx, double lly, double urx, double ury) {
  t3WX = wx;
  t3WY = wy;
  t3LLX = llx;
  t3LLY = lly;
  t3URX = urx;
  t3URY = ury;
  t3String = new GooString();
  writePS("STR");
  t3Cacheable = gTrue;
  t3NeedsRestore = gTrue;
}