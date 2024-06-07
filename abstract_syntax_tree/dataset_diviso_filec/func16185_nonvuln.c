libssh2_userauth_authenticated(LIBSSH2_SESSION * session)
{
    return (session->state & LIBSSH2_STATE_AUTHENTICATED)?1:0;
}