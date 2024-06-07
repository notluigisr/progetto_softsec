static bool needs_glob(ItemType t) {
        return IN_SET(t,
                      WRITE_FILE,
                      IGNORE_PATH,
                      IGNORE_DIRECTORY_PATH,
                      REMOVE_PATH,
                      RECURSIVE_REMOVE_PATH,
                      EMPTY_DIRECTORY,
                      ADJUST_MODE,
                      RELABEL_PATH,
                      RECURSIVE_RELABEL_PATH,
                      SET_XATTR,
                      RECURSIVE_SET_XATTR,
                      SET_ACL,
                      RECURSIVE_SET_ACL,
                      SET_ATTRIBUTE,
                      RECURSIVE_SET_ATTRIBUTE);
}