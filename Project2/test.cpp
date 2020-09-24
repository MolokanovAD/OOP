#include "pch.h"
#include "gtest/gtest.h"
#include "C:\Users\molok\source\repos\ProjectOOP2\Strophoid.h"
#include "C:\Users\molok\source\repos\ProjectOOP2\Strophoid.cpp"
const double error = 0.0001;
//Constructor
TEST(StrophoidConstructor, DefaultConstructor) {
  Project2::Strophoid a1;
  ASSERT_EQ(1, a1.getA());
}
TEST(StrophoidConstructor, InitConstructor) {
    Project2::Strophoid a2(-1);
    ASSERT_EQ(-1, a2.getA());
}
//Setter
TEST(StrophoidMethods, InitConstructor) {
    Project2::Strophoid a;
    a.setA(5);
    ASSERT_EQ(5, a.getA());
}
//Other Methods
TEST(StrophoidMethods, CurvRad) {
    Project2::Strophoid a(4);
    ASSERT_NEAR(4 * sqrt(2), a.curv_rad(), error);
    a.setA(-5.33);
    ASSERT_NEAR(5.33 * sqrt(2), a.curv_rad(), error);
}
TEST(StrophoidMethods, findY) {
    Project2::Strophoid a(4);
    ASSERT_NEAR(3.99 * sqrt(7.99 / 0.01), a.findY(3.99), error);
    ASSERT_ANY_THROW(a.findY(4.0));
    ASSERT_ANY_THROW(a.findY(-4.0001));
    a.setA(-5.33);
    ASSERT_ANY_THROW(a.findY(5.33001));
    ASSERT_ANY_THROW(a.findY(-5.33));
    ASSERT_NEAR(-5 * sqrt((-10.33) / (-0.33)),a.findY(-5), error);
}
TEST(StrophoidMethods, dist) {
    Project2::Strophoid a(8);
    ASSERT_ANY_THROW(a.dist(-1));
    ASSERT_ANY_THROW(a.dist(90));
    ASSERT_ANY_THROW(a.dist(270));
    ASSERT_ANY_THROW(a.dist(360));
    ASSERT_NEAR(8 * 2.23976411351, a.dist(70), error);
}
TEST(StrophoidMethods, S) {
    Project2::Strophoid a(-18);
    ASSERT_NEAR(324 * (2 + PI / 2), a.S(Project2::plus),error);
    ASSERT_NEAR(324 * (2 - PI / 2), a.S(Project2::minus), error);
}
TEST(StrophoidMethods, V) {
    Project2::Strophoid a(-18);
    ASSERT_NEAR(5832 * PI * (2 * log(2) - 4 / 3), a.V(), error);
}
TEST(StrophoidMethods, formula) {
    Project2::Strophoid a(-18);
    ASSERT_STREQ("y ^ 2 * (x + 18.00) + x ^ 2 * (x - 18.00) = 0", a.formula());
    a.setA(10);
    ASSERT_STREQ("y ^ 2 * (x - 10.00) + x ^ 2 * (x + 10.00) = 0", a.formula());
    a.setA(0);
    ASSERT_STREQ("y ^ 2 * x + x ^ 3 = 0", a.formula());
}
//
int _tmain(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}