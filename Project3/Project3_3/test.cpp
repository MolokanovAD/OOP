#include "pch.h"
#include "gtest/gtest.h"
#include "C:\Users\molok\source\repos\ProjectOOP3_3\Hex.h"
#include "C:\Users\molok\source\repos\ProjectOOP3_3\Hex.cpp"

TEST(HexConstructor, Constructors) {
    Project3_3::Hex a;
    char aa[8] = { 'a', 'a', 'a', '.', 'a', 'a', 'a', '\0' };
    char bb[36] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a','a','a', 'a', 'a', 'a', 'a', 'a', 'a','a', 'a', 'a', 'a', 'a', 'a', 'a', 'a','a', 'a', 'a', 'a', 'a', 'a', 'a', 'a','a','a', 'a', 'a','\0', };
    ASSERT_EQ('0', a.getSign());
    ASSERT_ANY_THROW(Project3_3::Hex b(aa));
    Project3_3::Hex c(bb);
    Project3_3::Hex copy(c);
    ASSERT_EQ('0', c.getSign());
    Project3_3::Hex d(-0x846fed),m(d);
    ASSERT_EQ('=', m.Compare(d));
    ASSERT_EQ('F', d.getSign());
    Project3_3::Hex dd(f(d));
    ASSERT_EQ('=', dd.Compare(d));
}
TEST(HexMethods, ParityCheck) {
    Project3_3::Hex a(0x5624fe), b(-0xdfabef), c;
    ASSERT_EQ(0, a.Check());
    ASSERT_EQ(1, b.Check());
    ASSERT_EQ(0, c.Check());
}
TEST(HexMethods, Compare) {
    char n1[5] = { '0','5','f','\0' }, n2[3] = { '5','F', '\0' };
    Project3_3::Hex a(0x5624f), b(-0xdfabe), c(n1), d(n2);
    ASSERT_EQ('>', a.Compare(b));
    ASSERT_EQ('>', a.Compare(c));
    ASSERT_EQ('<', b.Compare(c));
    ASSERT_EQ('=', c.Compare(d));
}
TEST(HexMethods, Convert) {
    Project3_3::Hex d(-0x846fed);
    Project3_3::Hex c = d.Convert().Convert();
    ASSERT_EQ('=', c.Compare(d));
}
TEST(HexMethods, Plus) {
    Project3_3::Hex a(0x5624f), b(-0xdfabe), c, d(-0x8986F);
    c = a + b;
    ASSERT_EQ('=', c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f', '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    char bd[34] = { '-', '1','f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','2' , '\0' };
    Project3_3::Hex e(bb), f(-1), t(0xfedabc), g(bc),r(bd);
    ASSERT_EQ('=', r.Compare(e + g));
}
TEST(HexMethods, Minus) {
    Project3_3::Hex a(0x5624f), b(-0xdfabe), c, d(-0x8986F);
    c = a + b;
    ASSERT_EQ('=', c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f', '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    Project3_3::Hex e(bb), f(2), t(-0xfedabc), g(bc);
    ASSERT_EQ('=', g.Compare(e - t));
}
TEST(HexMethods, Move) {
    Project3_3::Hex a(0x5624f), b(0x56), c, d(0x5600000);
    a >>= 3;
    ASSERT_EQ('=', a.Compare(b));
    a <<= 5;
    ASSERT_EQ('=', a.Compare(d));
    a >>= 20;
    ASSERT_EQ('=', a.Compare(c));
    b <<= 35;
    ASSERT_EQ('>', b.Compare(c));
}
