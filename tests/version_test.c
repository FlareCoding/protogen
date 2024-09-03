#define _GNU_SOURCE
#include "unity/unity.h"
#include <stdlib.h>
#include <string.h>

void setUp(void) {
    // Set up any necessary state before each test
}

void tearDown(void) {
    // Clean up any necessary state after each test
}

// Test function for version command
void test_version_command() {
    FILE *fp;
    char version_output[1024];

    // Run protogen --version and capture output
    fp = popen("./protogen --version", "r");
    TEST_ASSERT_NOT_NULL(fp);

    // Read output
    fgets(version_output, sizeof(version_output), fp);
    pclose(fp);

    // Assert the version output matches expected string
    TEST_ASSERT_EQUAL_STRING("ProtoGen version 1.0.0\n", version_output);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_version_command);
    return UNITY_END();
}

