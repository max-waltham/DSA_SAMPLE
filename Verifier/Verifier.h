#pragma once

#include <map>
#include <string.h>
#include "tommath.h"
#include "sha1.h"

class Verifier
{
private:
	void generateV(mp_int* v, mp_int* y, mp_int* p, mp_int* q, mp_int* g, mp_int* w, mp_int* r, mp_int* z);

public:
	Verifier(void);
	~Verifier(void);
	int verify(std::map<char, std::string>, std::string hirabun);
};

