#include <cstdlib>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "FooMock.h"

using namespace seamless;
using namespace std;

using ::testing::Return;

TEST(mock_test, get_result)
{  
    MockFoo mockFoo;
    string value = "Hello World!";
    EXPECT_CALL(mockFoo, get_from_rpc())
            .WillRepeatedly(Return(value));
    
    string result1 = mockFoo.get_from_rpc();
    string result2 = mockFoo.get_result();

    cout << "get_result() return : " << result1 << endl;
    cout << "get_result() return : " << result2 << endl;
    
    EXPECT_EQ(value, result1);
    EXPECT_EQ("reuslt is " + value, result2);
}

int main(int argc, char** argv) 
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

// g++ FooMain.cc -lpthread -lgtest -lgmock