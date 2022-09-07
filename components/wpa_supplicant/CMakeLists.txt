# cmake_minimum_required(VERSION 3.5)

# standard debug build

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWOLFSSL_USER_SETTINGS -DDEBUG_WOLFSSL -DENABLE_MQTT_TLS")

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWOLFSSL_USER_SETTINGS -DENABLE_MQTT_TLS -DCONFIG_ESP_TLS_USING_WOLFSSL")

set(WOLFSSL_ROOT "${PROJECT_DIR}/components/esp-wolfssl")



if (WOLFSSL_AES_DIRECT)
    message(STATUS  "")
    message(STATUS  "wpa_supplicant: found WOLFSSL_AES_DIRECT")
    message(STATUS  "")
endif()

if (WPA_TRACE_BFD)
    message(STATUS  "")
    message(STATUS  "wpa_supplicant: warning: do not define WPA_TRACE_BFD")
    message(STATUS  "")
endif()

if (CONFIG_TESTING_OPTIONS)
    message(STATUS  "")
    message(STATUS  "wpa_supplicant: warning: do not define CONFIG_TESTING_OPTIONS")
    message(STATUS  "")
endif()



# when CONFIG_WPA_MBEDTLS_CRYPTO is disabled in sdkconfig, we'll use wolfSSL
if (CONFIG_WPA_MBEDTLS_CRYPTO)
    set(WOLFSSL_WPA_SUPPLICANT "0")
else()
    # when WOLFSSL_WPA_SUPPLICANT is set to 1, we'll use wolfSSL instead of mbedTLS
    set(WOLFSSL_WPA_SUPPLICANT "0") # <<<<<< set to zero to always disable wolfSSL
endif()

# thanks stackoverflow: https://stackoverflow.com/questions/9298278/cmake-print-out-all-accessible-variables-in-a-script
if (0)
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif()

if (WOLFSSL_WPA_SUPPLICANT)
    message(STATUS  "")
    message(STATUS  "wpa_supplicant: WOLFSSL_WPA_SUPPLICANT")
    message(STATUS  "")

    set(srcs "port/os_xtensa.c"
    "src/ap/ap_config.c"
    "src/ap/ieee802_1x.c"
    "src/ap/wpa_auth.c"
    "src/ap/wpa_auth_ie.c"
    "src/common/sae.c"
    "src/common/wpa_common.c"
    "src/common/dpp.c"
    "src/crypto/aes-ctr.c"
    "src/crypto/aes-siv.c"
    "src/crypto/sha256-kdf.c"
    "src/crypto/aes-cbc.c"
    "src/crypto/aes-ccm.c"
    "src/crypto/aes-internal-dec.c"
    "src/crypto/aes-internal-enc.c"
    "src/crypto/aes-internal.c"
    "src/crypto/aes-omac1.c"
    "src/crypto/aes-unwrap.c"
    "src/crypto/aes-wrap.c"
    "src/crypto/aes-omac1.c"
    "src/crypto/bignum.c"
    "src/crypto/ccmp.c"

    # added wolfssl files:
    "src/crypto/crypto_wolfssl.c"
    "src/crypto/tls_wolfssl.c"
    "src/crypto/fips_prf_wolfssl.c"
#    "src/utils/os_unix.c"
#    "src/utils/os.h"

#    "src/crypto/crypto_mbedtls.c"
#    "src/crypto/crypto_mbedtls-bignum.c"
#    "src/crypto/crypto_mbedtls-ec.c"
    "src/crypto/crypto_ops.c"
    "src/crypto/crypto_internal-cipher.c"
    "src/crypto/crypto_internal-modexp.c"
    "src/crypto/crypto_internal-rsa.c"
#    "src/crypto/crypto_mbedtls-rsa.c"
    "src/crypto/crypto_internal.c"
    "src/crypto/des-internal.c"
    "src/crypto/dh_group5.c"
    "src/crypto/dh_groups.c"
    "src/crypto/md4-internal.c"
    "src/crypto/md5-internal.c"
    "src/crypto/md5.c"
    "src/crypto/ms_funcs.c"
    "src/crypto/rc4.c"
    "src/crypto/sha1-internal.c"
    "src/crypto/sha1-pbkdf2.c"
    "src/crypto/sha1.c"
    "src/crypto/sha256-internal.c"
    "src/crypto/sha256.c"
    "src/crypto/sha1-tlsprf.c"
    "src/crypto/sha256-tlsprf.c"
    "src/crypto/sha384-tlsprf.c"
    "src/crypto/sha256-prf.c"
    "src/eap_peer/chap.c"
    "src/eap_peer/eap.c"
    "src/eap_peer/eap_common.c"
    "src/eap_peer/eap_mschapv2.c"
    "src/eap_peer/eap_peap.c"
    "src/eap_peer/eap_peap_common.c"
    "src/eap_peer/eap_tls.c"
    "src/eap_peer/eap_tls_common.c"
    "src/eap_peer/eap_ttls.c"
    "src/eap_peer/mschapv2.c"
    "src/esp_supplicant/esp_hostap.c"
    "src/esp_supplicant/esp_wpa2.c"
    "src/esp_supplicant/esp_wpa_main.c"
    "src/esp_supplicant/esp_wpas_glue.c"
    "src/esp_supplicant/esp_wps.c"
    "src/esp_supplicant/esp_wpa3.c"
    "src/rsn_supp/pmksa_cache.c"
    "src/rsn_supp/wpa.c"
    "src/rsn_supp/wpa_ie.c"
    "src/utils/base64.c"
    "src/utils/common.c"
    "src/utils/ext_password.c"
    "src/utils/uuid.c"
    "src/utils/wpabuf.c"
    "src/utils/wpa_debug.c"
    "src/utils/json.c"
    "src/wps/wps.c"
    "src/wps/wps_attr_build.c"
    "src/wps/wps_attr_parse.c"
    "src/wps/wps_attr_process.c"
    "src/wps/wps_common.c"
    "src/wps/wps_dev_attr.c"
    "src/wps/wps_enrollee.c"
    "src/wps/wps_registrar.c"
    "src/wps/wps_validate.c")
else()
    message(STATUS  "")
    message(STATUS  "wpa_supplicant: default mbedTLS")
    message(STATUS  "")

    set(srcs "port/os_xtensa.c"
    "src/ap/ap_config.c"
    "src/ap/ieee802_1x.c"
    "src/ap/wpa_auth.c"
    "src/ap/wpa_auth_ie.c"
    "src/common/sae.c"
    "src/common/wpa_common.c"
    "src/common/dpp.c"
    "src/crypto/aes-ctr.c"
    "src/crypto/aes-siv.c"
    "src/crypto/sha256-kdf.c"
    "src/crypto/aes-cbc.c"
    "src/crypto/aes-ccm.c"
    "src/crypto/aes-internal-dec.c"
    "src/crypto/aes-internal-enc.c"
    "src/crypto/aes-internal.c"
    "src/crypto/aes-omac1.c"
    "src/crypto/aes-unwrap.c"
    "src/crypto/aes-wrap.c"
    "src/crypto/aes-omac1.c"
    "src/crypto/bignum.c"
    "src/crypto/ccmp.c"
    "src/crypto/crypto_mbedtls.c"
    "src/crypto/crypto_mbedtls-bignum.c"
    "src/crypto/crypto_mbedtls-ec.c"
    "src/crypto/crypto_ops.c"
    "src/crypto/crypto_internal-cipher.c"
    "src/crypto/crypto_internal-modexp.c"
    "src/crypto/crypto_internal-rsa.c"
    "src/crypto/crypto_mbedtls-rsa.c"
    "src/crypto/crypto_internal.c"
    "src/crypto/des-internal.c"
    "src/crypto/dh_group5.c"
    "src/crypto/dh_groups.c"
    "src/crypto/md4-internal.c"
    "src/crypto/md5-internal.c"
    "src/crypto/md5.c"
    "src/crypto/ms_funcs.c"
    "src/crypto/rc4.c"
    "src/crypto/sha1-internal.c"
    "src/crypto/sha1-pbkdf2.c"
    "src/crypto/sha1.c"
    "src/crypto/sha256-internal.c"
    "src/crypto/sha256.c"
    "src/crypto/sha1-tlsprf.c"
    "src/crypto/sha256-tlsprf.c"
    "src/crypto/sha384-tlsprf.c"
    "src/crypto/sha256-prf.c"
    "src/eap_peer/chap.c"
    "src/eap_peer/eap.c"
    "src/eap_peer/eap_common.c"
    "src/eap_peer/eap_mschapv2.c"
    "src/eap_peer/eap_peap.c"
    "src/eap_peer/eap_peap_common.c"
    "src/eap_peer/eap_tls.c"
    "src/eap_peer/eap_tls_common.c"
    "src/eap_peer/eap_ttls.c"
    "src/eap_peer/mschapv2.c"
    "src/esp_supplicant/esp_hostap.c"
    "src/esp_supplicant/esp_wpa2.c"
    "src/esp_supplicant/esp_wpa_main.c"
    "src/esp_supplicant/esp_wpas_glue.c"
    "src/esp_supplicant/esp_wps.c"
    "src/esp_supplicant/esp_wpa3.c"
    "src/rsn_supp/pmksa_cache.c"
    "src/rsn_supp/wpa.c"
    "src/rsn_supp/wpa_ie.c"
    "src/utils/base64.c"
    "src/utils/common.c"
    "src/utils/ext_password.c"
    "src/utils/uuid.c"
    "src/utils/wpabuf.c"
    "src/utils/wpa_debug.c"
    "src/utils/json.c"
    "src/wps/wps.c"
    "src/wps/wps_attr_build.c"
    "src/wps/wps_attr_parse.c"
    "src/wps/wps_attr_process.c"
    "src/wps/wps_common.c"
    "src/wps/wps_dev_attr.c"
    "src/wps/wps_enrollee.c"
    "src/wps/wps_registrar.c"
    "src/wps/wps_validate.c")
endif()

# CONFIG_WPA_MBEDTLS_CRYPTO is set in sdkconfig
if(CONFIG_WPA_MBEDTLS_CRYPTO)
    message(STATUS  "")
    message(STATUS  "wpa_supplicant: CONFIG_WPA_MBEDTLS_CRYPTO using src/crypto/tls_mbedtls.c")
    message(STATUS  "")

    set(tls_src "src/crypto/tls_mbedtls.c")
else()
    message(STATUS  "")
    message(STATUS  "wpa_supplicant: NOT CONFIG_WPA_MBEDTLS_CRYPTO using src/tls files")
    message(STATUS  "")

    set(tls_src
    "src/tls/asn1.c"
    "src/tls/bignum.c"
    "src/tls/pkcs1.c"
    "src/tls/pkcs5.c"
    "src/tls/pkcs8.c"
    "src/tls/rsa.c"
    "src/tls/tls_internal.c"
    "src/tls/tlsv1_client.c"
    "src/tls/tlsv1_client_read.c"
    "src/tls/tlsv1_client_write.c"
    "src/tls/tlsv1_common.c"
    "src/tls/tlsv1_cred.c"
    "src/tls/tlsv1_record.c"
    "src/tls/tlsv1_server.c"
    "src/tls/tlsv1_server_read.c"
    "src/tls/tlsv1_server_write.c"
    "src/tls/x509v3.c"
    )
endif()

if (CONFIG_ESP_TLS_USING_WOLFSSL)
    message(STATUS  "idf_component_register:  CONFIG_ESP_TLS_USING_WOLFSSL ${WOLFSSL_ROOT}")
    idf_component_register(
                        SRCS
                        	"${srcs}"
                        	"${tls_src}"
                        	src/crypto/crypto_wolfssl.c
                        	src/crypto/tls_wolfssl.c
                        	src/crypto/fips_prf_wolfssl.c
                        	src/utils/ip_addr.c
                        INCLUDE_DIRS include port/include include/esp_supplicant
                        PRIV_INCLUDE_DIRS
                        	src
                        	src/utils
                        	# src/esp_supplicant
                        	src/crypto
                        	src/common
                        	src/eap_common
                        	src/l2_packet
                        	"${WOLFSSL_ROOT}"
                        	"${WOLFSSL_ROOT}/wolfssl"
                        	"${WOLFSSL_ROOT}/wolfssl/wolfssl"
                        	"${WOLFSSL_ROOT}/include"
                        PRIV_REQUIRES mbedtls esp_timer)
else()
    message(STATUS  "idf_component_register:  mbedTLS")
    idf_component_register(SRCS "${srcs}" "${tls_src}"
                        INCLUDE_DIRS include port/include include/esp_supplicant
                        PRIV_INCLUDE_DIRS src
                        PRIV_REQUIRES mbedtls esp_timer)
endif()

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-strict-aliasing)
target_compile_definitions(${COMPONENT_LIB} PRIVATE
    __ets__
    ESP_SUPPLICANT
    IEEE8021X_EAPOL
    EAP_PEER_METHOD
    EAP_MSCHAPv2
    EAP_TTLS
    EAP_TLS
    EAP_PEAP
    USE_WPA2_TASK
    CONFIG_WPS2
    CONFIG_WPS_PIN
    USE_WPS_TASK
    ESPRESSIF_USE
    ESP32_WORKAROUND
    CONFIG_ECC
    CONFIG_IEEE80211W
    CONFIG_SHA256
    CONFIG_DPP
    )

if(CONFIG_ESP32_WIFI_ENABLE_WPA3_SAE)
    target_compile_definitions(${COMPONENT_LIB} PRIVATE CONFIG_WPA3_SAE)
endif()

set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3)

message(STATUS  "")
message(STATUS  "wpa_supplicant: using kinoo-firmware/components/esp-wolfssl/wolfssl")
message(STATUS  "PROJECT_DIR:     ${PROJECT_DIR}")
message(STATUS  "COMPONENT_NAME:  ${COMPONENT_NAME}")
message(STATUS  "COMPONENT_LIB:   ${COMPONENT_LIB}")
message(STATUS  "COMPONENT_DIR:   ${COMPONENT_DIR}")
message(STATUS  "COMPONENT_PATH:  ${COMPONENT_PATH}")
message(STATUS  "IDF_PATH:        ${IDF_PATH}")
message(STATUS  "PROJECT_DIR:     ${PROJECT_DIR}")
message(STATUS  "WOLFSSL_ROOT:    ${WOLFSSL_ROOT}")
message(STATUS  "WOLFSSL_AES_DIRECT:    ${WOLFSSL_AES_DIRECT}")
message(STATUS  "CONFIG_ESP_TLS_USING_WOLFSSL:    ${CONFIG_ESP_TLS_USING_WOLFSSL}")


message(STATUS  "")
