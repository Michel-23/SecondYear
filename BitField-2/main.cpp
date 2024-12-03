//#include "googletest-main/googletest/include/gtest/gtest.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*#include <iostream>
#include "BitField.h"*/
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

// int main(){
//     const size_t size = 38;

//     BitField bf(size);
//     BitField negBf(size);
//     BitField expNegBf(size);

//     std::vector<uint64_t> bits;
//     bits.push_back(0);
//     bits.push_back(1);
//     bits.push_back(14);
//     bits.push_back(16);
//     bits.push_back(33);
//     bits.push_back(37);

//     for (size_t i = 0; i < bits.size(); i++)
//       bf.SetBit(bits[i]);

//     negBf = ~bf;

//     for(size_t i = 0; i < size; i++)
//       expNegBf.SetBit(i);
//     for (size_t i = 0; i < bits.size(); i++)
//       expNegBf.ClrBit(bits[i]);

//     EXPECT_EQ(expNegBf, negBf);
//     return 0;
// }