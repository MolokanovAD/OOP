#include "pch.h"
#include "gtest/gtest.h"
#include "C:\Users\molok\source\repos\ProjectOOP3_1\Hex.h"
#include "C:\Users\molok\source\repos\ProjectOOP3_1\Hex.cpp"

TEST(HexConstructor, Constructors) {
    H16_1::Hex a;
    char aa[8] = { 'a', 'a', 'a', '.', 'a', 'a', 'a', 'a' }, bb[40] = { '-', 'a', 'a', 'e', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', '5', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'b', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'c', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'd', 'a', 'a', 'a', 'a' };
    ASSERT_EQ('0', a.getSign());
    ASSERT_ANY_THROW(H16_1::Hex b(aa));
    H16_1::Hex c(bb);
    ASSERT_EQ('F', c.getSign());
    H16_1::Hex d(-0x846fed);
    ASSERT_EQ('F', d.getSign());
}
TEST(HexMethods, ParityCheck) {
    H16_1::Hex a(0x5624fe), b(-0xdfabef), c;
    ASSERT_EQ(0, a.Check());
    ASSERT_EQ(1, b.Check());
    ASSERT_EQ(0, c.Check());
}
TEST(HexMethods, Compare) {
    char n1[5] = { '0','5','f','\0' }, n2[3] = { '5','F', '\0' };
    H16_1::Hex a(0x5624f), b(-0xdfabe), c(n1), d(n2);
    ASSERT_EQ(1, a.Compare(b));
    ASSERT_EQ(1, a.Compare(c));
    ASSERT_EQ(-1, b.Compare(c));
    ASSERT_EQ(0, c.Compare(d));
}
TEST(HexMethods, Convert) {
    H16_1::Hex d(-0x846fed);
    H16_1::Hex c = d.Convert().Convert();
    ASSERT_EQ(0, c.Compare(d));
}
TEST(HexMethods, Plus) {
    H16_1::Hex a(0x5624f), b(-0xdfabe), c, d(-0x8986F);
    c = a.Add(b);
    ASSERT_EQ(0, c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f' , '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    H16_1::Hex e(bb), f(-1), t(0xfedabc), g(bc);
    ASSERT_ANY_THROW(e.Add(f));
    ASSERT_EQ(0, g.Compare(e.Add(t)));
}
TEST(HexMethods, Minus) {
    H16_1::Hex a(0x5624f), b(-0xdfabe), c, d(-0x8986F);
    c = a.Add(b);
    ASSERT_EQ(0, c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f', '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    H16_1::Hex e(bb), f(2), t(-0xfedabc), g(bc);
    ASSERT_ANY_THROW(e.Decrease(f));
    ASSERT_EQ(0, g.Compare(e.Decrease(t)));
}
TEST(HexMethods, Move) {
    H16_1::Hex a(0x5624f), b(0x56), c, d(0x5600000);
    a.Move_r(3);
    ASSERT_EQ(0, a.Compare(b));
    a.Move_l(5);
    ASSERT_EQ(0, a.Compare(d));
    a.Move_r(20);
    ASSERT_EQ(0, a.Compare(c));
    b.Move_l(35);
    ASSERT_EQ(0, b.Compare(c));
}
int _tmain(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
