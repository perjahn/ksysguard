add_definitions(-DTRANSLATION_DOMAIN=\"ksysguard_plugins_process\")
if (libpcap_FOUND)
    add_subdirectory(network)
endif()
add_subdirectory(nvidia)
