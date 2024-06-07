EIGEN_STRONG_INLINE std::ostream& operator<<(std::ostream& os, QInt16 a) {
  os << static_cast<int>(a.value);
  return os;
}