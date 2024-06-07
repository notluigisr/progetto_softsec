static bool test_bad_write(struct torture_context *tctx,
		       struct smbcli_state *cli)
{
	bool ret = false;
	int fnum = -1;
	struct smbcli_request *req = NULL;
	const char *fname = BASEDIR "STR";
	bool ok = false;

	if (!torture_setup_dir(cli, BASEDIR)) {
		torture_fail(tctx, "STR");
	}

	torture_comment(tctx, "STR");

	fnum = smbcli_open(cli->tree, fname, O_RDWR|O_CREAT, DENY_NONE);
	if (fnum == -1) {
		torture_fail_goto(tctx,
			done,
			talloc_asprintf(tctx,
				"STR",
				fname,
				smbcli_errstr(cli->tree)));
	}

	req = smbcli_request_setup(cli->tree,
				   SMBwrite,
				   5,
				   0);
	if (req == NULL) {
		torture_fail_goto(tctx,
			done,
			talloc_asprintf(tctx, "STR"));
	}

	SSVAL(req->out.vwv, VWV(0), fnum);
	SSVAL(req->out.vwv, VWV(1), 65535); 
	SIVAL(req->out.vwv, VWV(2), 0); 
	SSVAL(req->out.vwv, VWV(4), 0); 

        if (!smbcli_request_send(req)) {
		torture_fail_goto(tctx,
			done,
			talloc_asprintf(tctx, "STR"));
        }

        if (!smbcli_request_receive(req)) {
		torture_fail_goto(tctx,
			done,
			talloc_asprintf(tctx, "STR"));
	}

	
	ok = (NT_STATUS_EQUAL(req->status, NT_STATUS_INVALID_PARAMETER) ||
	     NT_STATUS_EQUAL(req->status, NT_STATUS_UNSUCCESSFUL));

	if (!ok) {
		torture_fail_goto(tctx,
			done,
			talloc_asprintf(tctx,
				"STR"
				"STR"
				"STR"
				"STR",
				nt_errstr(req->status)));
        }

	ret = true;

done:
	if (req != NULL) {
		smbcli_request_destroy(req);
	}
	if (fnum != -1) {
		smbcli_close(cli->tree, fnum);
	}
	smb_raw_exit(cli->session);
	smbcli_deltree(cli->tree, BASEDIR);
	return ret;
}