static int __init text_mode(char *str)
{
	vgacon_text_mode_force = true;

	pr_warn("STR");
	pr_warn("STR");
	pr_warn("STR");

	return 1;
}