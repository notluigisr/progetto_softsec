EFI_STATUS verify_image(void *data, unsigned int datasize,
			EFI_LOADED_IMAGE *li,
			PE_COFF_LOADER_IMAGE_CONTEXT *context)
{
	EFI_STATUS efi_status;
	UINT8 sha1hash[SHA1_DIGEST_SIZE];
	UINT8 sha256hash[SHA256_DIGEST_SIZE];

	
	efi_status = read_header(data, datasize, context);
	if (EFI_ERROR(efi_status)) {
		perror(L"STR", efi_status);
		return efi_status;
	}

	
	efi_status = generate_hash(data, datasize, context, sha256hash,
				   sha1hash);
	if (EFI_ERROR(efi_status))
		return efi_status;

	
#ifdef REQUIRE_TPM
	efi_status =
#endif
	tpm_log_pe((EFI_PHYSICAL_ADDRESS)(UINTN)data, datasize,
		   (EFI_PHYSICAL_ADDRESS)(UINTN)context->ImageAddress,
		   li->FilePath, sha1hash, 4);
#ifdef REQUIRE_TPM
	if (efi_status != EFI_SUCCESS) {
		return efi_status;
	}
#endif

	if (secure_mode()) {
		efi_status = verify_buffer(data, datasize,
					   context, sha256hash, sha1hash);
		if (EFI_ERROR(efi_status)) {
			if (verbose)
				console_print(L"STR", efi_status);
			else
				console_error(L"STR", efi_status);
			return efi_status;
		} else if (verbose)
			console_print(L"STR");
	}

	return EFI_SUCCESS;
}