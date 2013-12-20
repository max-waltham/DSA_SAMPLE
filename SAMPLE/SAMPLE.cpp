// SAMPLE.cpp : コンソール アプリケーションのエントリ ポイントを定義します。

#include "stdafx.h"
#include <string>
#include <iostream>

#include "Generator.h"
#include "Verifier.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string hirabun("hirabunhirabunhirabun");

	Generator* g = new Generator();
	// g->generateKey(); //鍵生成は一度で良い
	
	std::map<char, std::string> keys = g->generateSign(hirabun);
	
	Verifier* v = new Verifier();

	//正しい文だとTRUE
	int r1 = v->verify(keys, hirabun);

	//ちょっと違う文だとFALSE
	std::string hirabun3("hirabunhirabunhirabu");
	int r2 = v->verify(keys, hirabun3);
	
	return 0;
}


