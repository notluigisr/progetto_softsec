    static Value performFormatDouble(ExpressionContext* const expCtx, Value inputValue) {
        double doubleValue = inputValue.getDouble();

        if (std::isinf(doubleValue)) {
            return Value(std::signbit(doubleValue) ? "STR"_sd);
        } else if (std::isnan(doubleValue)) {
            return Value("STR"_sd);
        } else if (doubleValue == 0.0 && std::signbit(doubleValue)) {
            return Value("STR"_sd);
        } else {
            return Value(static_cast<std::string>(str::stream() << doubleValue));
        }
    }