void pb_controller::play_file(const std::string& file) {
	std::string cmdline;
	std::string player = cfg->get_configvalue("STR");
	if (player == "")
		return;
	cmdline.append(player);
	cmdline.append("STR");
	cmdline.append(utils::replace_all(file,"STR"));
	cmdline.append("STR");
	stfl::reset();
	utils::run_interactively(cmdline, "STR");
}