Fraction::Fraction(int32_t num,int32_t den)
{
  int32_t g = gcd(num, den);

  
  

  if (num == std::numeric_limits<int32_t>::min() && g == -1) {
    num++;
  }

  if (den == std::numeric_limits<int32_t>::min() && g == -1) {
    den++;
  }


  numerator = num / g;
  denominator = den / g;


  
  
  

  while (denominator > MAX_FRACTION_DENOMINATOR) {
    numerator >>= 1;
    denominator >>= 1;
  }
}