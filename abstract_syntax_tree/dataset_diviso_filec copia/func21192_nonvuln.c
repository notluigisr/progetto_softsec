static int shadow_server_print_command_line_help(int argc, char** argv)
{
	char* str;
	size_t length;
	COMMAND_LINE_ARGUMENT_A* arg;
	COMMAND_LINE_ARGUMENT_A largs[ARRAYSIZE(shadow_args)];
	memcpy(largs, shadow_args, sizeof(shadow_args));
	if (argc < 1)
		return -1;

	WLog_INFO(TAG, "STR", argv[0]);
	WLog_INFO(TAG, "");
	WLog_INFO(TAG, "STR");
	WLog_INFO(TAG, "STR");
	WLog_INFO(TAG, "STR");
	WLog_INFO(TAG,
	          "STR");
	WLog_INFO(TAG, "");
	arg = largs;

	do
	{
		if (arg->Flags & COMMAND_LINE_VALUE_FLAG)
		{
			WLog_INFO(TAG, "STR");
			WLog_INFO(TAG, "STR", arg->Name);
			WLog_INFO(TAG, "STR", arg->Text);
		}
		else if ((arg->Flags & COMMAND_LINE_VALUE_REQUIRED) ||
		         (arg->Flags & COMMAND_LINE_VALUE_OPTIONAL))
		{
			WLog_INFO(TAG, "STR");

			if (arg->Format)
			{
				length = (strlen(arg->Name) + strlen(arg->Format) + 2);
				str = (char*)malloc(length + 1);

				if (!str)
					return -1;

				sprintf_s(str, length + 1, "STR", arg->Name, arg->Format);
				WLog_INFO(TAG, "STR", str);
				free(str);
			}
			else
			{
				WLog_INFO(TAG, "STR", arg->Name);
			}

			WLog_INFO(TAG, "STR", arg->Text);
		}
		else if (arg->Flags & COMMAND_LINE_VALUE_BOOL)
		{
			length = strlen(arg->Name) + 32;
			str = (char*)malloc(length + 1);

			if (!str)
				return -1;

			sprintf_s(str, length + 1, "STR");
			WLog_INFO(TAG, "STR");
			WLog_INFO(TAG, "STR", str);
			free(str);
			WLog_INFO(TAG, "STR", arg->Text);
		}
	} while ((arg = CommandLineFindNextArgumentA(arg)) != NULL);

	return 1;
}