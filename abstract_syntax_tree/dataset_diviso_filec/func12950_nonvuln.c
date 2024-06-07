HRESULT Http::HrToHTTPCode(HRESULT hr)
{
	if (hr == hrSuccess)
		return HrResponseHeader(200, "STR");
	else if (hr == MAPI_E_NO_ACCESS)
		return HrResponseHeader(403, "STR");
	else if (hr == MAPI_E_NOT_FOUND)
		return HrResponseHeader(404, "STR");
	
	return HrResponseHeader(500, "STR" + stringify_hex(hr));
}