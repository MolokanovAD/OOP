#include "pch.h"
#include "gtest/gtest.h"
#include "C:\Users\molok\source\repos\ProjectOOP3\Hex.h"
#include "C:\Users\molok\source\repos\ProjectOOP3\Hex.cpp"

TEST(HexConstructor, Constructors) {
    H16_2::Hex a;
    char aa[8] = { 'a', 'a', 'a', '.', 'a', 'a', 'a', 'a' },bb[40] = { '-', 'a', 'a', 'e', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', '5', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'b', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'c', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'd', 'a', 'a', 'a', 'a' };
    ASSERT_EQ('0', a.getSign());
    ASSERT_ANY_THROW(H16_2::Hex b(aa));
    H16_2::Hex c(bb);
    ASSERT_EQ('F', c.getSign());
    H16_2::Hex d(-0x846fed);
    ASSERT_EQ('F', d.getSign());
}
TEST(HexMethods, ParityCheck) {
    H16_2::Hex a(0x5624fe),b(-0xdfabef),c;
    ASSERT_EQ(0, a.Check());
    ASSERT_EQ(1, b.Check());
    ASSERT_EQ(0, c.Check());
}
TEST(HexMethods, Compare) {
    char n1[5] = { '0','5','f','\0' }, n2[3] = { '5','F', '\0' };
    H16_2::Hex a(0x5624f), b(-0xdfabe), c(n1),d(n2);
    ASSERT_EQ(1, a.Compare(b));
    ASSERT_EQ(1, a.Compare(c));
    ASSERT_EQ(-1, b.Compare(c));
    ASSERT_EQ(0, c.Compare(d));
}
TEST(HexMethods, Convert) {
    H16_2::Hex d(-0x846fed);
    H16_2::Hex c = d.Convert().Convert();
    ASSERT_EQ(0, c.Compare(d));
}
TEST(HexMethods, Plus) {
    H16_2::Hex a(0x5624f), b(-0xdfabe),c,d(-0x8986F);
    c = a + b;
    ASSERT_EQ(0, c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f', '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    H16_2::Hex e(bb),f(-1),t(0xfedabc),g(bc);
    ASSERT_ANY_THROW(e + f);
    ASSERT_EQ(0, g.Compare(e + t));
}
TEST(HexMethods, Minus) {
    H16_2::Hex a(0x5624f), b(-0xdfabe), c, d(-0x8986F);
    c = a + b;
    ASSERT_EQ(0, c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f', '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    H16_2::Hex e(bb), f(2), t(-0xfedabc), g(bc);
    ASSERT_ANY_THROW(e - f);
    ASSERT_EQ(0, g.Compare(e - t));
}
TEST(HexMethods, Move) {
    H16_2::Hex a(0x5624f), b(0x56), c, d(0x5600000),m;
    a >>= 3;
    ASSERT_ANY_THROW(a >>= -5);
    ASSERT_ANY_THROW(a <<= -1);
    ASSERT_EQ(0, a.Compare(b));
    a <<= 5;
    ASSERT_EQ(0, a.Compare(d));
    a = m;
    a <<= 0;
    ASSERT_EQ(0, a.Compare(m));
    a >>= 0;
    ASSERT_EQ(0, a.Compare(m));
    a >>= 20;
    ASSERT_EQ(0, a.Compare(c));
    b <<= 35;
    ASSERT_EQ(0, b.Compare(c));
}
int _tmain(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
