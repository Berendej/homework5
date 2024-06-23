cmake_minimum_required( VERSION 3.10 )
project( homework5 VERSION 0.1.1 )
add_executable( graphedit graphedit.cpp shapes.cpp graphdoc.cpp console_canvas.cpp controller.cpp )

# package part which enales
# run: cmake --build . --target package
install(TARGETS graphedit RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
set(CPACK_PACKAGE_CONTACT berrendej@gmail.com)
include(CPack)
