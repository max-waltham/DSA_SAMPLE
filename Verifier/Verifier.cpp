#include "StdAfx.h"
#include "Verifier.h"


Verifier::Verifier(void)
{
}


Verifier::~Verifier(void)
{
}

int Verifier::verify(std::map<char, std::string> map, std::string hira_bun)
{
   mp_int p, q, g, y, r, s;
   mp_init(&p);
   mp_init(&q);
   mp_init(&g);
   mp_init(&y);
   mp_init(&r);
   mp_init(&s);

   mp_read_radix(&p, map['p'].c_str(), 16);
   mp_read_radix(&q, map['q'].c_str(), 16);
   mp_read_radix(&g, map['g'].c_str(), 16);
   mp_read_radix(&y, map['y'].c_str(), 16);
   mp_read_radix(&r, map['r'].c_str(), 16);
   mp_read_radix(&s, map['s'].c_str(), 16);
   
   //平文のHash値を求める
   mp_int z;
   mp_init(&z);
   char buf[SHA1HashSize * 2 + 1];
   SHA1GenerateHash(hira_bun.c_str(), buf);
   mp_read_radix(&z, buf, 16);

   mp_int w, v;
   mp_init(&w);
   mp_init(&v);

   mp_invmod(&s, &q, &w); // generate W
   generateV(&v, &y, &p, &q, &g, &w, &r, &z);

   if (mp_cmp(&r, &v) == 0) {
      return TRUE;
   } else {
      return FALSE;
   }
}

void Verifier::generateV(mp_int* v, mp_int* y, mp_int* p, mp_int* q,
                         mp_int* g, mp_int* w, mp_int* r, mp_int* z)
{
   mp_int  u1, u2, u3, u4, t1, t2, t3, t4;
   mp_init(&u1);
   mp_init(&u2);
   mp_init(&u3);
   mp_init(&u4);
   mp_init(&t1);
   mp_init(&t2);
   mp_init(&t3);
   mp_init(&t4);

   mp_mul(z, w, &u1);
   mp_mod(&u1, q, &u2);   // remainderの代わり
   mp_mul(r, w, &u3);
   mp_mod(&u3, q, &u4);   // remainderの代わり

   mp_exptmod(g, &u2, p, &t1);
   mp_exptmod(y, &u4, p, &t2);

   mp_mul(&t1, &t2, &t3);
   mp_mod(&t3, p, &t4);   // remainderの代わり
   mp_mod(&t4, q, v);     // remainderの代わり

   mp_clear(&u1);
   mp_clear(&u2);
   mp_clear(&u3);
   mp_clear(&u4);
   mp_clear(&t1);
   mp_clear(&t2);
   mp_clear(&t3);
   mp_clear(&t4);
}