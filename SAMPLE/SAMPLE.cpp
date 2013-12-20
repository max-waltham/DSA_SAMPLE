// SAMPLE.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B

#include "stdafx.h"
#include <string>
#include <iostream>

#include "Generator.h"
#include "Verifier.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string hirabun("hirabunhirabunhirabun");

	Generator* g = new Generator();
	// g->generateKey(); //�������͈�x�ŗǂ�
	
	std::map<char, std::string> keys = g->generateSign(hirabun);
	
	Verifier* v = new Verifier();

	//������������TRUE
	int r1 = v->verify(keys, hirabun);

	//������ƈႤ������FALSE
	std::string hirabun3("hirabunhirabunhirabu");
	int r2 = v->verify(keys, hirabun3);
	
	return 0;
}


