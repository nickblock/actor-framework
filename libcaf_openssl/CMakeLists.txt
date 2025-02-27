project(caf_openssl C CXX)

# get header files; only needed by CMake generators,
# e.g., for creating proper Xcode projects
file(GLOB_RECURSE LIBCAF_OPENSSL_HDRS "caf/*.hpp")

# list cpp files excluding platform-dependent files
set(LIBCAF_OPENSSL_SRCS
  src/openssl/manager.cpp
  src/openssl/middleman_actor.cpp
  src/openssl/publish.cpp
  src/openssl/remote_actor.cpp
  src/openssl/session.cpp
)

add_custom_target(libcaf_openssl)

if (MINGW)
  set(OPENSSL_LIBRARIES ${OPENSSL_LIBRARIES} -lz)
endif()
# build shared library if not compiling static only
if (NOT CAF_BUILD_STATIC_ONLY)
  add_library(libcaf_openssl_shared SHARED
              ${LIBCAF_OPENSSL_SRCS} ${LIBCAF_OPENSSL_HDRS})
  target_link_libraries(libcaf_openssl_shared ${CAF_EXTRA_LDFLAGS}
                        ${CAF_LIBRARY_CORE} ${CAF_LIBRARY_IO} ${OPENSSL_LIBRARIES})

  if(NOT APPLE AND NOT WIN32)
    target_link_libraries(libcaf_openssl_shared "-pthread")
  endif()

  set_target_properties(libcaf_openssl_shared
                        PROPERTIES
                        SOVERSION ${CAF_VERSION}
                        VERSION ${CAF_LIB_VERSION}
                        OUTPUT_NAME caf_openssl)
  if (CYGWIN)
    install(TARGETS libcaf_openssl_shared RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  elseif (NOT WIN32)
    install(TARGETS libcaf_openssl_shared LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
  endif()
  add_dependencies(libcaf_openssl_shared libcaf_openssl)
endif ()

# build static library only if --build-static or --build-static-only was set
if (CAF_BUILD_STATIC_ONLY OR CAF_BUILD_STATIC)
  add_library(libcaf_openssl_static STATIC
              ${LIBCAF_OPENSSL_HDRS} ${LIBCAF_OPENSSL_SRCS})
  target_link_libraries(libcaf_openssl_static ${CAF_EXTRA_LDFLAGS}
                        ${CAF_LIBRARY_CORE_STATIC} ${CAF_LIBRARY_IO_STATIC} ${OPENSSL_LIBRARIES})
  set_target_properties(libcaf_openssl_static PROPERTIES
                        OUTPUT_NAME caf_openssl_static)
  if(NOT WIN32)
    install(TARGETS libcaf_openssl_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  endif()
  add_dependencies(libcaf_openssl_static libcaf_openssl)
endif ()

link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})

# install includes
if(NOT WIN32)
  install(DIRECTORY caf/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/caf FILES_MATCHING PATTERN "*.hpp")
endif()

