T ApplyPrelu(T input, T alpha) {
  return input >= 0.0 ? input : input * alpha;
}