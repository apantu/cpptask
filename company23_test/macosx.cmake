set(
    ARCHITECTURE
    x86_64
)


set_target_properties(
    ${PROJECT}
    PROPERTIES
        BUILD_WITH_INSTALL_RPATH
            1
        INSTALL_NAME_DIR
            "@rpath"
        LINK_FLAGS
            "-Wl,-rpath,@loader_path/${PROJECT}-${LIBRARY_VERSION}.d/ -Wl,-rpath,@loader_path/"
)