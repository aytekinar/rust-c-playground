include("build-release/CPackConfig.cmake")

set(CPACK_INSTALL_CMAKE_PROJECTS
  "build-debug;mylib;ALL;/"
  "build-release;mylib;ALL;/"
)
