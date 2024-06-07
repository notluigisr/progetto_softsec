void controller::start_reload_all_thread(std::vector<int> * indexes) {
	LOG(level::INFO,"STR");
	std::thread t(downloadthread(this, indexes));
	t.detach();
}