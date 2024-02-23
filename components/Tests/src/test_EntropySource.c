/*
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "OS_Crypto.h"

#include "lib_macros/Test.h"

#include "lib_debug/Debug.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <camkes.h>

// Use the EntropySource provided with TRENTOS
static OS_Crypto_Config_t cfgComp =
{
    .mode = OS_Crypto_MODE_LIBRARY,
    .entropy = IF_OS_ENTROPY_ASSIGN(
        entropy_rpc,
        entropy_port),
};
// Use the EntropySource provided as part of this test
static OS_Crypto_Config_t cfgOwn =
{
    .mode = OS_Crypto_MODE_LIBRARY,
    .entropy = IF_OS_ENTROPY_ASSIGN(
        myEntropy_rpc,
        myEntropy_port),
};

// Private Functions -----------------------------------------------------------

static void
test_EntropySource_component(
    void)
{
    OS_Crypto_Handle_t hCrypto;
    uint8_t buf[16];

    TEST_START();

    TEST_SUCCESS(OS_Crypto_init(&hCrypto, &cfgComp));
    TEST_SUCCESS(OS_CryptoRng_getBytes(hCrypto, 0, buf, sizeof(buf)));
    TEST_SUCCESS(OS_Crypto_free(hCrypto));

    TEST_FINISH();
}

static void
test_EntropySource_own(
    void)
{
    OS_Crypto_Handle_t hCrypto;
    uint8_t buf[16];

    TEST_START();

    TEST_SUCCESS(OS_Crypto_init(&hCrypto, &cfgOwn));
    TEST_SUCCESS(OS_CryptoRng_getBytes(hCrypto, 0, buf, sizeof(buf)));
    TEST_SUCCESS(OS_Crypto_free(hCrypto));

    TEST_FINISH();
}

// Public Functions ------------------------------------------------------------

int run()
{
    test_EntropySource_component();
    test_EntropySource_own();

    Debug_LOG_INFO("All tests successfully completed.");

    return 0;
}