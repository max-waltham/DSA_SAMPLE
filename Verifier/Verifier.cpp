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
   mp_int p, q, g, y;
   mp_init(&p);
   mp_init(&q);
   mp_init(&g);
   mp_init(&y);

   mp_int r, s, z;
   mp_init(&r);
   mp_init(&s);
   mp_init(&z);

   mp_read_radix(&p, map['p'].c_str(), 16);
   mp_read_radix(&q, map['q'].c_str(), 16);
   mp_read_radix(&g, map['g'].c_str(), 16);
   mp_read_radix(&y, map['y'].c_str(), 16);
   mp_read_radix(&r, map['r'].c_str(), 16);
   mp_read_radix(&s, map['s'].c_str(), 16);

   char buf[SHA1HashSize * 2 + 1];
   SHA1GenerateHash(hira_bun.c_str(), buf);
   mp_read_radix(&z, buf, 16);

   mp_int w, v;
   mp_init(&w);
   mp_init(&v);

   //((gz yr)(s-1) mod p) mod q = r

   mp_invmod(&s, &q, &w);    // generate W
   generateV(&v, &y, &p, &q, &g, &w, &r, &z);

   if (mp_cmp(&r, &v) == 0) {
      return TRUE;
   } else {
      return FALSE;
   }
}

void Verifier::generateV(mp_int * v, mp_int * y, mp_int * p, mp_int * q, mp_int * g, mp_int * w, mp_int* r, mp_int* z)
{
   mp_int temp;
   mp_int u1;
   mp_int u2;
   mp_int u2_2;
   mp_int t1;
   mp_int t2;
   mp_int t3;
   mp_int t5;
   mp_init(&temp);
   mp_init(&u1);
   mp_init(&u2);
   mp_init(&u2_2);
   mp_init(&t1);
   mp_init(&t2);
   mp_init(&t3);
   mp_init(&t5);

   mp_mul(z, w, &temp);
   mp_mod(&temp, q, &u1);   // remainderの代わり
   mp_mul(r, w, &u2_2);
   mp_mod(&u2_2, q, &u2);   // remainderの代わり

   mp_exptmod(g, &u1, p, &t1);
   mp_exptmod(y, &u2, p, &t2);

   mp_mul(&t1, &t2, &t3);
   mp_mod(&t3, p, &t5);   // remainderの代わり
   mp_mod(&t5, q, v);                  // remainderの代わり

   mp_clear(&temp);
   mp_clear(&u1);
   mp_clear(&u2);
   mp_clear(&u2_2);
   mp_clear(&t1);
   mp_clear(&t2);
   mp_clear(&t3);
   mp_clear(&t5);
}