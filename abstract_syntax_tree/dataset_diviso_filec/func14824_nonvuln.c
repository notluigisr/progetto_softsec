static bool io_match_link_files(struct io_kiocb *req,
				struct files_struct *files)
{
	struct io_kiocb *link;

	if (io_match_files(req, files))
		return true;
	if (req->flags & REQ_F_LINK_HEAD) {
		list_for_each_entry(link, &req->link_list, link_list) {
			if (io_match_files(link, files))
				return true;
		}
	}
	return false;
}