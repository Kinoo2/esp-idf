set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWOLFSSL_USER_SETTINGS -DENABLE_MQTT_TLS -DCONFIG_ESP_TLS_USING_WOLFSSL -DESP_PLATFORM")

# debugging:
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWOLFSSL_USER_SETTINGS -DDEBUG_WOLFSSL -DENABLE_MQTT_TLS -DCONFIG_ESP_TLS_USING_WOLFSSL -DESP_PLATFORM")

set(srcs esp_tls.c)
if(CONFIG_ESP_TLS_USING_MBEDTLS)
    message(STATUS  "")
    message(STATUS  "CONFIG_ESP_TLS_USING_MBEDTLS: esp_tls_mbedtls.c")
    message(STATUS  "")
    list(APPEND srcs
        "esp_tls_mbedtls.c")
endif()

if(CONFIG_ESP_TLS_USING_WOLFSSL)
    message(STATUS  "")
    message(STATUS  "CONFIG_ESP_TLS_USING_WOLFSSL: esp_tls_wolfssl.c")
    message(STATUS  "")
    list(APPEND srcs
        "esp_tls_wolfssl.c")
endif()

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "."
                    PRIV_INCLUDE_DIRS "private_include"
                    REQUIRES mbedtls
                    PRIV_REQUIRES lwip nghttp)

if(CONFIG_ESP_TLS_USING_WOLFSSL)
    idf_component_get_property(wolfssl esp-wolfssl COMPONENT_LIB)
    target_link_libraries(${COMPONENT_LIB} PUBLIC ${wolfssl})
endif()

if(CONFIG_ESP_TLS_USE_SE)
    idf_component_get_property(cryptoauthlib esp-cryptoauthlib COMPONENT_LIB)
    target_link_libraries(${COMPONENT_LIB} PUBLIC ${cryptoauthlib})
endif()


set(CMAKE_CURRENT_SOURCE_DIR ".")
set(ESP_TLS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# some non-essential diagnostic messages:
get_filename_component(ESP_TLS_PATH "esp_tls.c"  REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")

message(STATUS  "")
message(STATUS  "kc v4.2.2")
message(STATUS  "ESP_TLS_PATH:             ${ESP_TLS_PATH}")
message(STATUS  "COMPONENT_LIB:            ${COMPONENT_LIB}")
message(STATUS  "CMAKE_CURRENT_LIST_DIR:   ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS  "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS  "ESP_TLS_ROOT:             ${ESP_TLS_ROOT}")
message(STATUS  "CMAKE_HOME_DIRECTORY:     ${CMAKE_HOME_DIRECTORY}")
message(STATUS  "")
