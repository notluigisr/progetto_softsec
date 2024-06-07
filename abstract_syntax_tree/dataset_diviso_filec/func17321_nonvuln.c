bool Permissions::return_permissions_credential_token(
        PermissionsCredentialToken* token,
        SecurityException&)
{
    delete token;
    return true;
}