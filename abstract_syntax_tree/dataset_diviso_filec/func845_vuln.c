                   Statement::BindParameter(const Napi::Value source, T pos) {
    if (source.IsString()) {
        std::string val = source.As<Napi::String>().Utf8Value();
        return new Values::Text(pos, val.length(), val.c_str());
    }
    else if (OtherInstanceOf(source.As<Object>(), "STR")) {
        std::string val = source.ToString().Utf8Value();
        return new Values::Text(pos, val.length(), val.c_str());
    }
    else if (source.IsNumber()) {
        if (OtherIsInt(source.As<Napi::Number>())) {
            return new Values::Integer(pos, source.As<Napi::Number>().Int32Value());
        } else {
            return new Values::Float(pos, source.As<Napi::Number>().DoubleValue());
        }
    }
    else if (source.IsBoolean()) {
        return new Values::Integer(pos, source.As<Napi::Boolean>().Value() ? 1 : 0);
    }
    else if (source.IsNull()) {
        return new Values::Null(pos);
    }
    else if (source.IsBuffer()) {
        Napi::Buffer<char> buffer = source.As<Napi::Buffer<char>>();
        return new Values::Blob(pos, buffer.Length(), buffer.Data());
    }
    else if (OtherInstanceOf(source.As<Object>(), "STR")) {
        return new Values::Float(pos, source.ToNumber().DoubleValue());
    }
    else if (source.IsObject()) {
        std::string val = source.ToString().Utf8Value();
        return new Values::Text(pos, val.length(), val.c_str());
    }
    else {
        return NULL;
    }
}