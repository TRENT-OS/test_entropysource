#
# Test entropy source
#
# Copyright (C) 2019-2020, Hensoldt Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)

os_set_config_file(system_config.h)

project(test_entropysource C)

DeclareCAmkESComponent(test_EntropySource
    SOURCES
        components/Tests/src/test_EntropySource.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_core_api
        os_libs
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

DeclareAndCreateCamkESSystem(main.camkes)
GenerateSimulateScript()
