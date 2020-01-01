/** @file bugme_chinrem_gcd.cpp
 *
 * A small program exposing historical bug in poly_cra function. */

/*
 *  GiNaC Copyright (C) 1999-2020 Johannes Gutenberg University Mainz, Germany
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "ginac.h"

#include <iostream>
#include <string>
using namespace std;

namespace GiNaC {
extern ex chinrem_gcd(const ex& A, const ex& B);
}

using namespace GiNaC;

static const std::string p1_srep("\
-936639990-14679334842*x^9-6214147095*x^35+22219362387*x^69-31276301429*x^25+1199649580*x^98+2134905268*x^56+25591410149*x^72+5507703343*x^11+18467021749*x^43+11196778577*x^85+26050790733*x^29-178435747*x^2+1890708440*x^88-561107347*x^13-31038290506*x^51-1330154020*x^15+23467669465*x^59-3966988360*x^16+26794929142*x^38+11598735101*x^75-8608995580*x^3-30174373832*x^46+3580061526*x^91+7814495607*x^20+6624766926*x^78-11990574398*x^54-6863205889*x^33-319408644*x^65-11580405260*x^41-9654281719*x^81+23532819511*x^24-3890383043*x^94+27682281779*x^62+1363904895*x^68-272899085*x^49-933592128*x^97-2954269379*x^28+8432066353*x^36+14038262112*x^71-5474416933*x^84+741141010*x^100+38375274669*x^57-19509035058*x^44-1029159530*x^87+17276957972*x^8+23471621465*x^19-4745283802*x^74-15331409214*x^23-1261023993*x^90+17469329915*x^52-7544450778*x^64+12293848678*x^10-12162845828*x^39+11912265375*x^77-35110566664*x^27-5872201799*x^60+16636451249*x^80-6663332709*x^12+26248623452*x^47+2292551912*x^93-13410537172*x^14+4255578378*x^55+11614165303*x^31-6270990007*x^34-6744628155*x^67+3692350529*x^96-17204774085*x^63-11157075535*x^18+4275663006*x^70+18517327396*x^42+2030662033*x^83-3435911855*x^50-227816977*x^99+4507833875*x-41046742100*x^37+9385606040*x^73-5892518210*x^22+512268187*x^86+9183261708*x^58-2542140060*x^4-19627087954*x^45+142491112*x^89-4846605217*x^26-4503859503*x^30-38388107386*x^32+2123912816*x^5-2508504600*x^76-15282350857*x^53-12217636980*x^40-4828562936*x^79+1788729074*x^6-967823912*x^92+6436149609*x^7+44704228721*x^61+21474090980*x^17+36034512058*x^66+10918084347*x^21+1913801599*x^82+1530941050*x^48-7104898913*x^95");

static const std::string p2_srep("\
1882371920+29943249139*x^9-21558061051*x^35+24497174109*x^69+3363043648*x^25+5186524611*x^98-17753230977*x^56+16461882236*x^72+11039962159*x^11-85814533599*x^43-12986831645*x^85+4813620791*x^29-2133682609*x^2+9141433582*x^88-14841292646*x^13+19494168654*x^51-426278523*x^15-18246235652*x^59-12424469513*x^16-14414308862*x^38-16262001424*x^75+1584505491*x^3+6616907060*x^46+9411879011*x^91+7056872613*x^20+29675566382*x^78-48441925739*x^54+12038293769*x^33-22463329638*x^65+21957440404*x^41+26252749471*x^81-28689993421*x^24+1190623161*x^94-3323333429*x^62+778770195*x^68-23673866858*x^49+10263027507*x^97+29115114125*x^28-34230002076*x^36-217623403*x^71-6344703601*x^84+2789684836*x^100-44973929094*x^57-6061422988*x^44+18964048763*x^87+3160532878*x^8-8039690791*x^19-5750277357*x^74+5544486596*x^23+1800283356*x^90-8174921854*x^52+2577247520*x^64-1088265300*x^10+18566882873*x^39+12678193001*x^77-7204610489*x^27+9980611956*x^60+12672890141*x^80+4463462090*x^12-30937311949*x^47-3883570155*x^93+7561875663*x^14-3850452489*x^55+20714527103*x^31-9973372012*x^34+440594870*x^67+10385086102*x^96-20693764726*x^63+11049483001*x^18-11578701274*x^70-5548876327*x^42+20393397488*x^83+20531692560*x^50+1309311388*x^99-7521320830*x-2750892631*x^37-6001481047*x^73+7149046134*x^22+10287410396*x^86+7332053562*x^58-1135211878*x^4-7420079075*x^45+9742202475*x^89-214559874*x^26+29530802947*x^30-2280622009*x^32-4237029618*x^5+13760397067*x^76+18073788685*x^53+2485463829*x^40+1889202286*x^79+8841198971*x^6+13562767020*x^92+110919258*x^7+6961020716*x^61+11700952246*x^17-13528331424*x^66-19801882818*x^21+25061328813*x^82+1553111326*x^48+4638169279*x^95");

static void check_poly_cra()
{
	parser the_parser;
	ex p1 = the_parser(p1_srep);
	ex p2 = the_parser(p2_srep);
	ex g = chinrem_gcd(p1, p2);
}

static void check_extract_integer_content()
{
	parser readme;
	ex A = readme("1/282901891126422365*(x + y)");
	ex B = readme("165888/282901891126422365*(x - y)");
	ex g = chinrem_gcd(A, B);
}

static void integer_coeff_braindamage()
{
	parser readme;
	ex A = readme("3*x^2 + 1");
	ex B = readme("9*x^2 + 1");
	ex g = chinrem_gcd(A, B);
	if (!g.is_equal(ex(1))) {
		std::cerr << "expected 1, got " << g << std::endl;
		throw std::logic_error("chinrem_gcd miscomputed integer content");
	}
}

int main(int argc, char** argv)
{
	cout << "checking for bugs in poly_cra() and friends " << flush;
	check_poly_cra();
	check_extract_integer_content();
	integer_coeff_braindamage();
	cout << "not found.";
	return 0;
}
