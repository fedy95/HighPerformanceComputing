#include <gtest/gtest.h>

#include "../Matrix/Matrix.h"

TEST(getNumRowsTest, getNumRowsTest) {
    auto *matrix = new Matrix(4, 40);
    ASSERT_EQ(4, matrix->getNumRows());
    delete(matrix);
}

TEST(getNumColumnsTest, getNumColumnsTest) {
    auto *matrix = new Matrix(4, 40);
    ASSERT_EQ(40, matrix->getNumRows());
    delete(matrix);
}
//
//TEST(showFirstMatrix, showFirstMatrix) {
//
//}
//
//TEST(showSecondMatrix, showSecondMatrix) {
//
//}
//
//TEST(showResultMatrix, showResultMatrix) {
//
//}
//
//TEST(getExecutingTimeWithOmp, getExecutingTimeWithOmp) {
//
//}
//
//TEST(getExecutingTimeWithoutOmp, getExecutingTimeWithoutOmp) {
//
//}
//
//TEST(multiplyTwoMatricesWithOmpDefault, multiplyTwoMatricesWithOmpDefault) {
//
//}
//
//TEST(multiplyTwoMatricesWithOmpStatic, multiplyTwoMatricesWithOmpStatic) {
//
//}
//
//TEST(multiplyTwoMatricesWithOmpDynamic, multiplyTwoMatricesWithOmpDynamic) {
//
//}
//
//TEST(multiplyTwoMatricesWithOmpGuided, multiplyTwoMatricesWithOmpGuided) {
//
//}
//
//TEST(multiplyTwoMatricesWithOmpRuntime, multiplyTwoMatricesWithOmpRuntime) {
//
//}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}