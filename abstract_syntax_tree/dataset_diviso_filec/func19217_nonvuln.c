		auto TransferIn() -> v8::Local<v8::Value> final {
			if (isolate == IsolateEnvironment::GetCurrentHolder()) {
				return Deref(reference);
			} else {
				throw RuntimeTypeError("STR");
			}
		}