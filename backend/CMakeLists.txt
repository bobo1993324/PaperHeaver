include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
    Paperheaverbackend_SRCS
    modules/Paperheaver/backend.cpp
    modules/Paperheaver/filemodel.cpp
    modules/Paperheaver/filetreeitem.cpp
    modules/Paperheaver/googledrivemodel.cpp
    modules/Paperheaver/mytype.cpp
)

add_library(Paperheaverbackend MODULE
    ${Paperheaverbackend_SRCS}
)

set_target_properties(Paperheaverbackend PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY Paperheaver)

qt5_use_modules(Paperheaverbackend Gui Qml Quick)

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(Paperheaverbackend-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/Paperheaver/qmldir ${CMAKE_CURRENT_BINARY_DIR}/Paperheaver
    DEPENDS ${QMLFILES}
)

# Install plugin file
install(TARGETS Paperheaverbackend DESTINATION ${QT_IMPORTS_DIR}/Paperheaver/)
install(FILES   modules/Paperheaver/qmldir DESTINATION ${QT_IMPORTS_DIR}/Paperheaver/)

