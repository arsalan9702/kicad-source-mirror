set(GSEIM_BUILD_DIR ${PROJECT_BINARY_DIR}/resources/gseim)
file(MAKE_DIRECTORY ${GSEIM_BUILD_DIR})

configure_file(
    slvparms.in
    ${GSEIM_BUILD_DIR}/slvparms.in
    COPYONLY
)
configure_file(
    GSEIM_Library.kicad_sym
    ${GSEIM_BUILD_DIR}/GSEIM_Library.kicad_sym
    COPYONLY
)

# Copy data + binaries into the build tree (used when running via
# KICAD_RUN_FROM_BUILD_DIR=1)
file(COPY
    ebe
    xbe
    sub
    bin
    gseim_aux
    DESTINATION ${GSEIM_BUILD_DIR}
)

# file(COPY)'s default permission propagation from source has proven
# unreliable in practice for these two binaries (mtime matched source,
# yet exec bit was still dropped) - force the bits explicitly instead
# of relying on inherited/source permissions.
file(CHMOD ${GSEIM_BUILD_DIR}/bin/run_gseim
    PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)
file(CHMOD ${GSEIM_BUILD_DIR}/bin/gseim_plotter/gseim_plotter
    PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)

# ---------------------------------------------------------------------------
# Install rules
# ---------------------------------------------------------------------------

# Data directories - no executables inside, USE_SOURCE_PERMISSIONS is fine
install(
    DIRECTORY
        ebe
        xbe
        sub
        gseim_aux
    DESTINATION ${KICAD_DATA}/resources/gseim
    USE_SOURCE_PERMISSIONS
)

# run_gseim - installed with explicit PERMISSIONS so the exec bit is
# guaranteed regardless of the source file's mode
install(
    FILES bin/run_gseim
    DESTINATION ${KICAD_DATA}/resources/gseim/bin
    PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)

# gseim_plotter/ - install the supporting _internal/ payload (libraries,
# data files) via USE_SOURCE_PERMISSIONS, but EXCLUDE the launcher binary
# from this directory install and install it separately below with
# forced PERMISSIONS - same guarantee as run_gseim above.
install(
    DIRECTORY
        bin/gseim_plotter
    DESTINATION ${KICAD_DATA}/resources/gseim/bin
    USE_SOURCE_PERMISSIONS
    PATTERN "gseim_plotter/gseim_plotter" EXCLUDE
)
install(
    FILES bin/gseim_plotter/gseim_plotter
    DESTINATION ${KICAD_DATA}/resources/gseim/bin/gseim_plotter
    PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)

# Standalone files
install(
    FILES
        slvparms.in
        GSEIM_Library.kicad_sym
    DESTINATION ${KICAD_DATA}/resources/gseim
)