constexpr bool sub(stdx::type_identity_t<T> a, stdx::type_identity_t<T> b, T* r) {
#ifdef _MSC_VER
    return !SafeSubtract(a, b, *r);
#else
    return __builtin_sub_overflow(a, b, r);
#endif
}