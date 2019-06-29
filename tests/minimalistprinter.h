#ifndef MINIMALISTPRINTER_H
#define MINIMALISTPRINTER_H

#include "gtest/gtest.h"

class MinimalistPrinter : public ::testing::EmptyTestEventListener {
public:
    std::string testCaseName, testName;

    virtual void OnTestProgramStart (const ::testing::UnitTest& testProgram) {
        printf ("\nUnit test results\n");
        printf ("---------------------\n");
    }

    virtual void OnTestProgramEnd (const ::testing::UnitTest& testProgram) {
        printf ("---------------------\n");
        printf ("\n%d tests run\n", testProgram.test_to_run_count());
        printf ("%d tests passed\n", testProgram.successful_test_count());
        printf ("%d tests failed\n\n", testProgram.failed_test_count());
        printf ("---------------------\n");
    }

    virtual void OnTestCaseStart (const ::testing::TestCase& testCase) {
        testCaseName = std::string (testCase.name());
        printf ("\nTest case %s\n", testCaseName.c_str());
    }

    virtual void OnTestCaseEnd (const testing::TestCase& testCase) {
        printf ("%d tests run\n", testCase.test_to_run_count());
        printf ("%d tests passed\n", testCase.successful_test_count());
        printf ("%d tests failed\n\n", testCase.failed_test_count());
    }

    virtual void OnTestStart (const ::testing::TestInfo& test_info) {
        testName = std::string (test_info.name());
    }

    virtual void OnTestEnd (const ::testing::TestInfo& test_info) {
        printf("%s Test %s.%s\n", test_info.result() -> Passed() ? "PASSED" : "FAILED", test_info.test_case_name(), test_info.name());
    }

    // Called after a failed assertion or a SUCCEED() invocation.
    virtual void OnTestPartResult(
    const ::testing::TestPartResult& test_part_result) {
        std::string summary = test_part_result.summary();
        size_t position = 0;
        for (position = summary.find ("\n"); position != std::string::npos; position = summary.find ("\n", position)) {
            summary.replace (position, 1, " ");
        }
        summary = "[" + testCaseName + "." + testName + "] " + summary;
        printf ("*** %s:%d: %s: %s\n",
            test_part_result.file_name(),
            test_part_result.line_number(),
            test_part_result.failed() ? "Failure" : "Success",
            summary.c_str());
    }


};
#endif // MINIMALISTPRINTER_H
