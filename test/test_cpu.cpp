//
// Created by Ville Välimaa on 08/04/2017.
//

#include "gtest/gtest.h"
#include "cpu.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestProgramMemoryLoading, TEST_MEMORY) {
    cpu c;
    c.init();
    c.load("PONG");
    EXPECT_EQ(50, 50);
}

// TOO LARGE FILE

// OK SIZE FILE

// ZERO SIZE FILE