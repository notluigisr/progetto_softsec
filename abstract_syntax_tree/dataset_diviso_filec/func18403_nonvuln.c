EIGEN_STRONG_INLINE QInt32 operator*(const QUInt16 a, const QInt32 b) {
  return QInt32(static_cast<int32_t>(a.value) * b.value);
}