#
# Test entropy source
#
# Copyright (C) 2019-2024, HENSOLDT Cyber GmbH
# 
# SPDX-License-Identifier: GPL-2.0-or-later
#
# For commercial licensing, contact: info.cyber@hensoldt.net
#

cmake_minimum_required(VERSION 3.7.2)

#-------------------------------------------------------------------------------
# use the SDK
find_package("os-sdk" REQUIRED)
os_sdk_set_defaults()
os_sdk_setup(CONFIG_FILE "system_config.h" CONFIG_PROJECT "system_config")


#-------------------------------------------------------------------------------
project(test_entropysource C)

DeclareCAmkESComponent(test_EntropySource
    SOURCES
        components/Tests/src/test_EntropySource.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_core_api
        lib_debug
        lib_macros
        os_crypto
)

# Use the existing entropy source, which at this point is just some dummy
EntropySource_DeclareCAmkESComponent(
    EntropySource
)

# Use our own implementation of the EntropySource interface
EntropySource_DeclareCAmkESComponent(
    MyEntropy
    SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/components/MyEntropy/MyEntropy.c"
)

os_sdk_create_CAmkES_system("main.camkes")
