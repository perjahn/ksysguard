set(SOURCES
    client.cpp
    ksysguarddaemon.cpp
)

set_source_files_properties("ksysguard_iface.xml"
    PROPERTIES INCLUDE "../ksysguard-backend/types.h" )
qt5_add_dbus_adaptor(SOURCES "ksysguard_iface.xml" ksysguarddaemon.h KSysGuardDaemon)

add_library(ksystemstats_core STATIC ${SOURCES})
target_link_libraries(ksystemstats_core PUBLIC Qt5::Core Qt5::DBus KF5::CoreAddons KSysGuard::StatsBackend )

add_executable(ksystemstats main.cpp)
target_link_libraries(ksystemstats ksystemstats_core)

install(TARGETS ksystemstats DESTINATION ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

kdbusaddons_generate_dbus_service_file(ksystemstats org.kde.ksystemstats ${KDE_INSTALL_FULL_BINDIR})

add_subdirectory(test)

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()
