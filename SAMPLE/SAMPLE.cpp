// SAMPLE.cpp : コンソール アプリケーションのエントリ ポイントを定義します。

#include "stdafx.h"
#include <string>
#include <iostream>
/*
 * license
 * LibTomMath is public domain. As should all quality software be.
 * Tom St Denis
 */
#include "tommath.h"

#include "Generator.h"
#include "Verifier.h"
int libtommathTest(){
	mp_int a;
	mp_int b;
	mp_int answer;
	mp_init(&a);
	mp_init(&b);
	mp_init(&answer);

	mp_read_radix(&a, "10", 10);
	mp_read_radix(&b, "ef012", 16);
	mp_copy(&a, &b);
	for (int i = 1; i < 2; i++) {
		mp_mul(&a, &b, &answer);
		mp_copy(&answer, &a);
	}
	char anschar[1000];
	mp_toradix(&answer, anschar,10);
	//printf(anschar);
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	libtommathTest();
	std::string hirabun("hirabunhirabunhirabun");
	Generator* g = new Generator();
	std::map<char, std::string> map;
	g->generateKey();
	map = g->generateSign(hirabun);
	
	Verifier* v = new Verifier();
	std::string hirabun2("hirabunhirabunhirabun");
	int r1 = v->verify(map, hirabun2);
	std::string hirabun3("hirabunhirabunhirabu");
	int r2 = v->verify(map, hirabun3);
	return 0;

}


