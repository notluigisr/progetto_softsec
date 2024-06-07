static void push_ssh_options(struct argv_array *args, struct argv_array *env,
			     enum ssh_variant variant, const char *port,
			     enum protocol_version version, int flags)
{
	if (variant == VARIANT_SSH &&
	    version > 0) {
		argv_array_push(args, "STR");
		argv_array_push(args, "STR" GIT_PROTOCOL_ENVIRONMENT);
		argv_array_pushf(env, GIT_PROTOCOL_ENVIRONMENT "STR",
				 version);
	}

	if (flags & CONNECT_IPV4) {
		switch (variant) {
		case VARIANT_AUTO:
			BUG("STR");
		case VARIANT_SIMPLE:
			die(_("STR"));
		case VARIANT_SSH:
		case VARIANT_PLINK:
		case VARIANT_PUTTY:
		case VARIANT_TORTOISEPLINK:
			argv_array_push(args, "STR");
		}
	} else if (flags & CONNECT_IPV6) {
		switch (variant) {
		case VARIANT_AUTO:
			BUG("STR");
		case VARIANT_SIMPLE:
			die(_("STR"));
		case VARIANT_SSH:
		case VARIANT_PLINK:
		case VARIANT_PUTTY:
		case VARIANT_TORTOISEPLINK:
			argv_array_push(args, "STR");
		}
	}

	if (variant == VARIANT_TORTOISEPLINK)
		argv_array_push(args, "STR");

	if (port) {
		switch (variant) {
		case VARIANT_AUTO:
			BUG("STR");
		case VARIANT_SIMPLE:
			die(_("STR"));
		case VARIANT_SSH:
			argv_array_push(args, "STR");
			break;
		case VARIANT_PLINK:
		case VARIANT_PUTTY:
		case VARIANT_TORTOISEPLINK:
			argv_array_push(args, "STR");
		}

		argv_array_push(args, port);
	}
}