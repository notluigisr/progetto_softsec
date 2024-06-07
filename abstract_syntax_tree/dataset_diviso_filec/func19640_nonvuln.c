BGD_DECLARE(int) gdLayerMultiply (int dst, int src)
{
	int a1, a2, r1, r2, g1, g2, b1, b2;
	a1 = gdAlphaMax - gdTrueColorGetAlpha(src);
	a2 = gdAlphaMax - gdTrueColorGetAlpha(dst);

	r1 = gdRedMax - (a1 * (gdRedMax - gdTrueColorGetRed(src))) / gdAlphaMax;
	r2 = gdRedMax - (a2 * (gdRedMax - gdTrueColorGetRed(dst))) / gdAlphaMax;
	g1 = gdGreenMax - (a1 * (gdGreenMax - gdTrueColorGetGreen(src))) / gdAlphaMax;
	g2 = gdGreenMax - (a2 * (gdGreenMax - gdTrueColorGetGreen(dst))) / gdAlphaMax;
	b1 = gdBlueMax - (a1 * (gdBlueMax - gdTrueColorGetBlue(src))) / gdAlphaMax;
	b2 = gdBlueMax - (a2 * (gdBlueMax - gdTrueColorGetBlue(dst))) / gdAlphaMax ;

	a1 = gdAlphaMax - a1;
	a2 = gdAlphaMax - a2;
	return ( ((a1*a2/gdAlphaMax) << 24) +
			 ((r1*r2/gdRedMax) << 16) +
			 ((g1*g2/gdGreenMax) << 8) +
			 ((b1*b2/gdBlueMax))
		);
}