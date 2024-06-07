TPMU_ATTEST_Marshal(TPMU_ATTEST  *source, BYTE **buffer, INT32 *size, UINT32 selector)
{
    UINT16 written = 0;

    switch (selector) {
      case TPM_ST_ATTEST_CERTIFY:
	written += TPMS_CERTIFY_INFO_Marshal(&source->certify, buffer, size);
	break;
      case TPM_ST_ATTEST_CREATION:
	written += TPMS_CREATION_INFO_Marshal(&source->creation, buffer, size);
	break;
      case TPM_ST_ATTEST_QUOTE:
	written += TPMS_QUOTE_INFO_Marshal(&source->quote, buffer, size);
	break;
      case TPM_ST_ATTEST_COMMAND_AUDIT:
	written += TPMS_COMMAND_AUDIT_INFO_Marshal(&source->commandAudit, buffer, size);
	break;
      case TPM_ST_ATTEST_SESSION_AUDIT:
	written += TPMS_SESSION_AUDIT_INFO_Marshal(&source->sessionAudit, buffer, size);
	break;
      case TPM_ST_ATTEST_TIME:
	written += TPMS_TIME_ATTEST_INFO_Marshal(&source->time, buffer, size);
	break;
      case TPM_ST_ATTEST_NV:
	written += TPMS_NV_CERTIFY_INFO_Marshal(&source->nv, buffer, size);
	break;
      case TPM_ST_ATTEST_NV_DIGEST:
	written += TPMS_NV_DIGEST_CERTIFY_INFO_Marshal(&source->nvDigest, buffer, size);
	break;
      default:
	pAssert(FALSE);
    }
    return written;
}