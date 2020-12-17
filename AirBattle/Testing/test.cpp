#include "pch.h"
#include "..\ProjectOOP4lib\Anti_Rocket.h"
#include "..\ProjectOOP4lib\Disguise.h"
#include "..\ProjectOOP4lib\Gun.h"
#include "..\ProjectOOP4lib\Launcher.h"
#include "..\ProjectOOP4lib\Mission.h"
#include "..\ProjectOOP4lib\Plane.h"
#include "..\ProjectOOP4lib\Radio.h"
#include "..\ProjectOOP4lib\Scout.h"
#include "..\ProjectOOP4lib\Squad.h"
#include "..\ProjectOOP4lib\Table.h"
#include "..\ProjectOOP4lib\Weapon.h"
#include "..\ProjectOOP4lib\moving.h"

using namespace AirBattle;
TEST(GUN, GunMethods) {//constr,shot
	ASSERT_ANY_THROW(Gun GNT(2, 1, 4, -1));
	Gun GN;
	std::string squad_name[2] = { "First","Second" };
	std::string en_squad_name[2] = { "Enemy1","Enemy2" };
	Mission M(2, 2, squad_name, en_squad_name, 500, 500);
	ASSERT_EQ(false, GN.shot(476, 12, M.get_table(false)["Enemy1"].get_plane(0)->get_distance(0, 0), M.get_table(false), 12345));//далеко
	ASSERT_EQ(false, GN.shot(376, 12, M.get_table(false)["Enemy1"].get_plane(0)->get_distance(0, 0), M.get_table(false), 16345));//мимо
	ASSERT_EQ(false, GN.shot(376, 12, M.get_table(false)["Enemy1"].get_plane(0)->get_distance(0, 0), M.get_table(false), 20345));//перезарядка
	ASSERT_EQ(true, GN.shot(476, 12, M.get_table(false)["Enemy1"].get_plane(0)->get_distance(186, 0), M.get_table(false), 25345));
}
TEST(LAUNCHER, LauncherMethods) {//constr,shot
	ASSERT_ANY_THROW(Launcher GNT(-1, 1, 4, 0));
	Launcher LCH;
	std::string squad_name[2] = { "First","Second" };
	std::string en_squad_name[2] = { "Enemy1","Enemy2" };
	Mission M(2, 2, squad_name, en_squad_name, 900, 1100);
	ASSERT_EQ(false, LCH.shot(1076, 12, M.get_table(false)["Enemy1"].get_plane(0)->get_distance(0, 0), M.get_table(false), 12345));//далеко
	ASSERT_EQ(false, LCH.shot(476, 12, M.get_table(false)["Enemy1"].get_plane(0)->get_distance(99, 0), M.get_table(false), 16345));//мимо
	ASSERT_EQ(false, LCH.shot(1076, 12, M.get_table(false)["Enemy1"].get_plane(0)->get_distance(99, 0), M.get_table(false), 16345));//перезарядка
	ASSERT_EQ(true, LCH.shot(1076, 12, M.get_table(false)["Enemy1"].get_plane(0)->get_distance(99, 0), M.get_table(false), 20900));
}
TEST(PLANE, PlaneMethods) {//Delete_weapon,Add_weapon,Fire
	Anti_Rocket AR(0, 0, 1400, 1400, 5, 5, 1000, 3, 5);
	ASSERT_ANY_THROW(AR.Delete_weapon(AR.get_weapons_total() + 1));
	AR.Delete_weapon(3);
	Gun* new_weapon = new Gun;
	AR.Add_weapon(new_weapon);
	std::string squad_name[2] = { "First","Second" };
	std::string en_squad_name[2] = { "Enemy1","Enemy2" };
	Mission M(2, 2, squad_name, en_squad_name, 1000, 1100);
	Plane& pl = M.find_plane(squad_name[0], 0, true);
	ASSERT_EQ(false, pl.Fire(M.get_table(false)["Enemy1"].get_plane(0), M.get_table(true), M.get_table(false), 12333, pl.get_radio_detection()));//далеко
	pl.set_x(200);
	ASSERT_EQ(false, pl.Fire(M.get_table(false)["Enemy1"].get_plane(0), M.get_table(true), M.get_table(false), 12333, pl.get_radio_detection()));//враг не обнаружен
	pl.set_x(1000);
	ASSERT_EQ(true, pl.Fire(M.get_table(false)["Enemy1"].get_plane(0), M.get_table(true), M.get_table(false), 12333, pl.get_radio_detection()));
}
TEST(DISGUISE, DisgMethods) {//getDamage
	Disguise D;
	D.getDamage(200, 1.18, true, 0.0);//выстрел из пушки с идеальной точнотью (с учетом маскировки)
	ASSERT_EQ(1200, D.get_hp());
	D.getDamage(300, 1.0, false, 0.0);//выстрел из ракетницы 
	ASSERT_EQ(900, D.get_hp());
	D.getDamage(100, 0.0, true, 0.0);//выстрел из пушки с нулевой точностью
	ASSERT_EQ(900, D.get_hp());
	Disguise D1 = disg_f();
	Disguise D2(D1);
}
TEST(ANTIROCKET, AntiRMethods) {//getDamage
	Anti_Rocket A;
	A.getDamage(200, 1.0, false, 1.0);//выстрел из ракетницы без подавления систем ПРО
	ASSERT_EQ(1400, A.get_hp());
	A.getDamage(300, 1.0, true, 0.0);//выстрел из пушки с идеальной точнотью
	ASSERT_EQ(1100, A.get_hp());
	A.getDamage(100, 0.0, false, 0.0);//выстрел из ракетницы с полным подавлением системы ПРО
	ASSERT_EQ(1000, A.get_hp());
	Anti_Rocket A1 = antir_f();
	Anti_Rocket A2(A1);
}
TEST(RADIO, RadioMethods) {//getDamage
	Radio R;
	R.getDamage(200, 1.0, false, 1.0);//выстрел из ракетницы 
	ASSERT_EQ(1200, R.get_hp());
	R.getDamage(300, 1.0, true, 0.0);//выстрел из пушки с идеальной точнотью
	ASSERT_EQ(900, R.get_hp());
	R.getDamage(100, 0.0, true, 0.0);//выстрел из пушки с нулевой точнотью
	ASSERT_EQ(900, R.get_hp());
	Radio R1 = radio_f();
	Radio R2(R1);
}
TEST(SCOUT, ScoutMethods) {//getDamage
	Scout S;
	S.getDamage(200, 1.0, false, 1.0);//выстрел из ракетницы 
	ASSERT_EQ(800, S.get_hp());
	S.getDamage(300, 1.0, true, 0.0);//выстрел из пушки с идеальной точнотью
	ASSERT_EQ(500, S.get_hp());
	S.getDamage(100, 0.0, true, 0.0);//выстрел из пушки с нулевой точнотью
	ASSERT_EQ(500, S.get_hp());
	Scout S1(scout_f());
	Scout S2(S1);
}
TEST(SQUAD, SquadMethods) {//get_det_decr, get_det_range, get_disg_decr, get_plane, noticed, Delete, Add
	std::string squad_name[4] = { "First","Second","Third","Fourths" };
	std::string en_squad_name[4] = { "Enemy1","Enemy2","Enemy3","Enemy4" };
	Mission M(4, 4, squad_name, en_squad_name, 900, 1800);
	Squad b(1500, 0, 0, 1, 1, 1, 1);
	ASSERT_ANY_THROW(b.get_plane(4));
	ASSERT_EQ(1400, b.get_plane(0)->get_hp());
	ASSERT_ANY_THROW(b.get_plane(-1));
	ASSERT_EQ(0.97, b.get_det_decr(1501, 1));
	ASSERT_EQ(0.9215, b.get_disg_decr(1501, 1));
	ASSERT_EQ(0.92, b.get_pro_decr(1501, 1));
	ASSERT_EQ(650, b.get_det_range());
	ASSERT_EQ(true, b.noticed(M.get_table(false).find_by_coordinates(1776, 12), M.get_table(true), M.get_table(false)));
	Squad d(1000, 0, 0, 1, 1, 1, 1);
	ASSERT_EQ(false, d.noticed(M.get_table(false).find_by_coordinates(1776, 12), M.get_table(true), M.get_table(false)));//далеко
	d.Delete(*d.get_plane(0));
	ASSERT_EQ(3, d.get_N());
	d.Add(new Anti_Rocket);
	ASSERT_EQ(4, d.get_N());
	ASSERT_ANY_THROW(d.Add(new Anti_Rocket));//звено переполнено
}
TEST(TABLE, TableMethods) {//get_det_decr, get_pro_decr, get_disg_decr, operator[],find_by_coordinates, Add, Delete, find
	std::string squad_name[4] = { "First","Second","Third","Fourths" };
	std::string en_squad_name[4] = { "Enemy1","Enemy2","Enemy3","Enemy4" };
	Mission M(4, 4, squad_name, en_squad_name, 900, 1800);
	double radio = pow(0.97, 4);
	double scout = pow(0.95, 4);
	ASSERT_DOUBLE_EQ(radio, M.get_table(true).get_det_decr(1, 200));
	ASSERT_DOUBLE_EQ(0.92 * 0.92 * 0.92 * 0.92, M.get_table(true).get_pro_decr(1, 200));
	ASSERT_DOUBLE_EQ(scout * radio, M.get_table(true).get_disg_decr(1, 200));
	ASSERT_EQ(M.get_table(false)["Enemy1"].get_plane(0)->get_x(), M.get_table(false).find_by_coordinates(1776, 12).get_x());
	Squad c(500, 0, 0, 1, 1, 1, 1);
	M.get_table(true).Add(&c, "NEW");
	ASSERT_EQ(5, M.get_table(true).get_size());
	M.get_table(true).Delete("First");
	ASSERT_EQ(4, M.get_table(true).get_size());
	ASSERT_EQ(M.get_table(true).find("First"), M.get_table(true).end());
	ASSERT_EQ((*M.get_table(true).find("NEW")).second->getx(), c.getx());
}
TEST(MISSION, MissionMethods) {//find_squad, find_plane
	std::string squad_name[4] = { "First","Second","Third","Fourths" };
	std::string en_squad_name[4] = { "Enemy1","Enemy2","Enemy3","Enemy4" };
	Mission M(4, 4, squad_name, en_squad_name, 900, 1800);
	ASSERT_EQ(0, M.find_squad("First", true).gety());
	ASSERT_EQ(12, M.find_plane("First", 0, true).get_y());
	ASSERT_ANY_THROW(M.find_plane("First", 5, true));
	ASSERT_ANY_THROW(M.find_squad("First1", true));
}