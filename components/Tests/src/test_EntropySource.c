#include "OS_Crypto.h"

#include "TestMacros.h"

#include "LibDebug/Debug.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <camkes.h>

// Use the EntropySource provided with TRENTOS-M
static OS_Crypto_Config_t cfgComp =
{
    .mode = OS_Crypto_MODE_LIBRARY_ONLY,
    .library.entropy = OS_CRYPTO_ASSIGN_EntropySource(
        entropySource_rpc,
        entropySource_dp),
};
// Use the EntropySource provided as part of this test
static OS_Crypto_Config_t cfgOwn =
{
    .mode = OS_Crypto_MODE_LIBRARY_ONLY,
    .library.entropy = OS_CRYPTO_ASSIGN_EntropySource(
        myEntropy_rpc,
        myEntropy_dp),
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