static void __exit efi_capsule_loader_exit(void)
{
	misc_deregister(&efi_capsule_misc);
}