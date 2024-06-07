NativeModule::NativeModule(const std::string& filename) : init(nullptr) {
	if (uv_dlopen(filename.c_str(), &lib) != 0) {
		throw RuntimeGenericError("STR");
	}
	if (uv_dlsym(&lib, "STR", reinterpret_cast<void**>(&init)) != 0 || init == nullptr) {
		uv_dlclose(&lib);
		throw RuntimeGenericError("STR");
	}
}