#include "StdAfx.h"
#include "Generator.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tommath.h"

Generator::Generator()
{
}

Generator::~Generator(void)
{
}

std::map<char, std::string> Generator::generateSign(std::string hira_bun)
{   
   mp_int p, q, g, y, x;
   mp_init(&p);
   mp_init(&q);
   mp_init(&g);
   mp_init(&y);
   mp_init(&x);

   mp_read_radix(&p, DSA_P, 16);
   mp_read_radix(&q, DSA_Q, 16);
   mp_read_radix(&g, DSA_G, 16);
   mp_read_radix(&x, DSA_X, 16);
   mp_read_radix(&y, DSA_Y, 16);
   
   //������Hash�l�����߂�
   mp_int z;
   mp_init(&z);
   char buf[SHA1HashSize * 2 + 1];
   SHA1GenerateHash(hira_bun.c_str(), buf);
   mp_read_radix(&z, buf, 16);

   /*���A�������߂� (k��0�ȊO�̃����_���Ȑ����j
   r = (g^k mod p) mod q �Ƃ��܂�
   s = k^(-1) (z + x r) mod q �Ƃ��܂�*/

   mp_int r, s, k, zero;
   mp_init(&r);
   mp_init(&s);
   mp_init(&k);
   mp_init(&zero);

   mp_int t1, t2, t3;
   mp_init(&t1);
   mp_init(&t2);
   mp_init(&t3);

   mp_zero(&r);
   mp_zero(&s);
   mp_zero(&zero);

   while (mp_cmp(&r, &zero) == 0 || 
      mp_cmp(&s, &zero) == 0) {

      //k��I�� (�����_���A�̂���E�E)
      srand((unsigned)clock());
      int k_int = rand() + 1;
      mp_set_int(&k, k_int);

      //r   = (g^k mod p) mod q
      mp_exptmod(&g, &k, &p, &t1);
      mp_mod(&t1, &q, &r);

      //s = k^(-1) (z + x r) mod q
      mp_mul(&x, &r, &t1);
      mp_add(&z, &t1, &t2);
      mp_invmod(&k, &q, &t3);
      mp_mul(&t2, &t3, &s);
   }

   //������߂�l�ɃZ�b�g�B
   std::map<char, std::string> map;

   char anschar[1000];
   map['p'] = DSA_P;
   map['q'] = DSA_Q;
   map['g'] = DSA_G;
   mp_tohex(&r, anschar);
   map['r'] = anschar;
   mp_tohex(&s, anschar);
   map['s'] = anschar;
   mp_tohex(&y, anschar);
   map['y'] = anschar;

   return map;
}
void Generator::generateKey()
{
   mp_int p, q, g, y, x;
   mp_init(&p);
   mp_init(&q);
   mp_init(&g);
   mp_init(&y);
   mp_init(&x);

   mp_read_radix(&p, DSA_P, 16);
   mp_read_radix(&q, DSA_Q, 16);
   mp_read_radix(&g, DSA_G, 16);
   /*�閧���E���J�������܂�
     x �� 0 < x < q  �őI��Ŕ閧���Ƃ���
     y = (g^x) mod p �����J���Ƃ���*/

   //�閧��x��I�� : q��菬������Ηǂ�(���R�Ɍ��߂�j
   char x_str[] = "1234567890abcdef1234567890abcdef";
   mp_read_radix(&x, x_str, 16);

   //y = (g^x) mod p
   mp_exptmod(&g, &x, &p, &y);

   char anschar[1000];
   mp_tohex(&x, anschar);
   std::cout << "#define DSA_X \"" << anschar << "\"" << std::endl;
   mp_tohex(&y, anschar);
   std::cout << "#define DSA_Y \"" << anschar << "\"" << std::endl;
}