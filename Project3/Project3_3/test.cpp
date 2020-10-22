#include "pch.h"
#include "gtest/gtest.h"
#include "C:\Users\molok\source\repos\ProjectOOP3_3\Hex.h"
#include "C:\Users\molok\source\repos\ProjectOOP3_3\Hex.cpp"
#include "C:\Users\molok\source\repos\ProjectOOP3_3\f.h"
#include "C:\Users\molok\source\repos\ProjectOOP3_3\f.cpp"
TEST(HexConstructor, Constructors) {
    H16_3::Hex a;
    char aa[8] = { 'a', 'a', 'a', '.', 'a', 'a', 'a', '\0' };
    char bb[36] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a','a','a', 'a', 'a', 'a', 'a', 'a', 'a','a', 'a', 'a', 'a', 'a', 'a', 'a', 'a','a', 'a', 'a', 'a', 'a', 'a', 'a', 'a','a','a', 'a', 'a','\0', };
    ASSERT_EQ('0', a.getSign());
    ASSERT_ANY_THROW(H16_3::Hex b(aa));
    H16_3::Hex c(bb);
    H16_3::Hex copy(c);
    ASSERT_EQ('0', c.getSign());
    H16_3::Hex d(-0x846fed), m(d);
    ASSERT_EQ(0, m.Compare(d));
    ASSERT_EQ('F', d.getSign());
    H16_3::Hex dd(f(d));
    ASSERT_EQ(0, dd.Compare(d));
}
TEST(HexMethods, ParityCheck) {
    H16_3::Hex a(0x5624fe), b(-0xdfabef), c;
    ASSERT_EQ(0, a.Check());
    ASSERT_EQ(1, b.Check());
    ASSERT_EQ(0, c.Check());
}
TEST(HexMethods, Compare) {
    char n1[5] = { '0','5','f','\0' }, n2[3] = { '5','F', '\0' };
    H16_3::Hex a(0x5624f), b(-0xdfabe), c(n1), d(n2);
    ASSERT_EQ(1, a.Compare(b));
    ASSERT_EQ(1, a.Compare(c));
    ASSERT_EQ(-1, b.Compare(c));
    ASSERT_EQ(0, c.Compare(d));
}
TEST(HexMethods, Convert) {
    H16_3::Hex d(-0x846fed);
    H16_3::Hex c = d.Convert().Convert();
    ASSERT_EQ(0, c.Compare(d));
}
TEST(HexMethods, Plus) {
    H16_3::Hex a(0x5624f), b(-0xdfabe), c, d(-0x8986F);
    c = a + b;
    ASSERT_EQ(0, c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f', '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    char bd[34] = { '-', '1','f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','2' , '\0' };
    H16_3::Hex e(bb), f(-1), t(0xfedabc), g(bc), r(bd);
    ASSERT_EQ(0, r.Compare(e + g));
}
TEST(HexMethods, Minus) {
    H16_3::Hex a(0x5624f), b(0xdfabe), c, d(-0x8986F);
    c = a - b;
    ASSERT_EQ(0, c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f', '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    H16_3::Hex e(bb), f(2), t(-0xfedabc), g(bc);
    ASSERT_EQ(0, g.Compare(e - t));
}
TEST(HexMethods, Move) {
    H16_3::Hex a(0x5624f), b(0x56), c, d(0x5600000),k(500);
    ASSERT_ANY_THROW(k >>= -1);
    ASSERT_ANY_THROW(k <<= -1);
    a >>= 3;
    ASSERT_EQ(0, a.Compare(b));
    a <<= 5;
    ASSERT_EQ(0, a.Compare(d));
    a >>= 20;
    ASSERT_EQ(0, a.Compare(c));
    b <<= 35;
    ASSERT_EQ(1, b.Compare(c));
}
TEST(HexMethods, Assignment) {
    H16_3::Hex a(0x5624f), b(0x56), c, d(0x5600000);
    H16_3::Hex move_c(f(a)),move_a;
    move_a = FF(b);
    H16_3::Hex copy_a;
    copy_a = move_a;
    ASSERT_EQ(0, a.Compare(move_c));
    ASSERT_EQ(0, move_a.Compare(b));
    ASSERT_EQ(0, move_a.Compare(copy_a));
}
int _tmain(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}