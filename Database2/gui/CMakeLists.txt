qt_add_executable(DatabaseApp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    dialog.cpp
    dialog.h
    dialog.ui
    add_dialog.cpp
    add_dialog.h
    add_dialog.ui
)

target_link_libraries(DatabaseApp PRIVATE Qt6::Widgets Database)

target_include_directories(DatabaseApp PRIVATE
    ${CMAKE_SOURCE_DIR}/database
)
