/*

  Harjoitus 3

  Optimoi suorien tunnistus. Älä muuta kääntäjäoptioita.
  Pidä ohjelma yksisäikeisenä.

  Vertaa alkuperäistä ja optimoitua versiota:

  - kuinka paljon enemmän muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?
  Muisti:
  Nopeus RAW, STD, -O0: 5.4s vs 20.0s vs 20.5s

  Vaikuttaa siltä et toi std::unordered_map hashäys kun ettii bitsetillä vie kaiken ajan. 
  En tiiä pystyiskö sen jotenki tekemään niin et se ei aina tekis häshiä siitä bitsetistä mikä tehään siitä kädestä

  Käännös: gcc straight.c -o straight

*/

#include <stdio.h>
#include <time.h>

#include <algorithm>
#include <map>
#include <unordered_map>
#include <bitset>

//Use OptimizedRaw, OptimizedSTD, OptimizedNot
#define OptimizedNot


inline int is_straight(int *k);
inline void is_quadsorfullhouse(int *k, int& y, int& j);


#if defined(OptimizedSTD)

std::unordered_map<std::bitset<13>, int> HandLookUp{
  {std::bitset<13>("1000000001111"), 1}, {std::bitset<13>("1111100000000"), 1}, {std::bitset<13>("0000000011111"), 1}, {std::bitset<13>("0000000111110"), 1},
  {std::bitset<13>("0000001111100"), 1}, {std::bitset<13>("0000011111000"), 1}, {std::bitset<13>("0000111110000"), 1}, {std::bitset<13>("0001111100000"), 1},
  {std::bitset<13>("0011111000000"), 1}, {std::bitset<13>("0111110000000"), 1}
};
std::bitset<13> BitwiseHand{0};

#endif

#if defined(OptimizedRaw)

const int STRAIGHT_COUNT = 10;
const int BIT_MASKS[STRAIGHT_COUNT] = {
    0b0000000011111, // A-2-3-4-5 (treated as 1-2-3-4-5)
    0b0000000111110, // 2-3-4-5-6
    0b0000001111100, // 3-4-5-6-7
    0b0000011111000, // 4-5-6-7-8
    0b0000111110000, // 5-6-7-8-9
    0b0001111100000, // 6-7-8-9-10
    0b0011111000000, // 7-8-9-10-J
    0b0111110000000, // 8-9-10-J-Q
    0b1111100000000, // 9-10-J-Q-K
    0b1000000001111  // 10-J-Q-K-A
};


#endif

int main()
{
  /*

    Käydään läpi kaikki viiden kortin permutaatiot, ja lasketaan
    kuin monta suoraa (värisuoraa tai tavallista) löytyy.

    Ks. Wikipedia http://en.wikipedia.org/wiki/Poker_probability :

    Four of A Kind  624    combinations
    Fullhouses      3744   combinations
    Royal flush     4      combinations
    Straight flush  36     combinations
    Straight        10,200 combinations

    Koska 5 korttia voi olla 5 x 4 x 3 x 2 x 1 = 120 järjestyksessä,
    pitäisi suoria löytyä (10200 + 36 + 4) x 120 = 1228800 kappaletta. 

  */
  int k0, k1, k2, k3, k4; /* Pakan kortit, 0..51*/
  int k[5]; /* Korttien numeroarvot, 2..14*/
  int suoria; /* Suorien lkm*/
  int neloset = 0;
  int fullhouse = 0;
  clock_t t1, t2;

  t1 = clock();
  suoria = 0;
  for (k0 = 0; k0 < 52; ++k0) {
  for (k1 = 0; k1 < 52; ++k1) { if (k1==k0)continue;
  for (k2 = 0; k2 < 52; ++k2) { if (k2==k0||k2==k1)continue;
  for (k3 = 0; k3 < 52; ++k3) { if (k3==k0||k3==k1||k3==k2)continue;
  for (k4 = 0; k4 < 52; ++k4) { if (k4==k0||k4==k1||k4==k2||k4==k3)continue;

	    /*
	      Lasketaan korttien numeroarvot ja
	      tarkistetaan onko suora.
	    */
	    k[0] = (k0 % 13) + 2;
	    k[1] = (k1 % 13) + 2;
	    k[2] = (k2 % 13) + 2;
	    k[3] = (k3 % 13) + 2;
	    k[4] = (k4 % 13) + 2;
	    if (is_straight(k))
	      ++suoria;
      is_quadsorfullhouse(k, neloset, fullhouse);
	  }}}}}
  t2 = clock();
  printf("Suoria     : %d kpl (oikea arvo 1228800)\n", suoria);
  printf("Nelosia     : %d kpl (oikea arvo 74880)\n", neloset);
  printf("Tayskasia     : %d kpl (oikea arvo 449280)\n", fullhouse);
  printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);
 
  return 0;
}


/*
  Parametrina 5 pelikortin numeroarvoa k, 2..14 (ei välttämättä
  numerojärjesteyksessä).

  Palauttaa 1, jos numeroarvot voidaan järjestää siten, että
  ne muodostavat suoran (esim. 4,5,6,7,8).

  Huom! Ässää (arvo 14) voidaan käyttää suorissa myös arvona 1
  (esim. 1,2,3,4,5).
*/
inline int is_straight(int *k)
{

  #if defined(OptimizedRaw)

  //Convert card values to a bit mask
  int handbits = 0;
  for (int i = 0; i < 5; ++i)
  {
    handbits |= (1 << (k[i] - 2));
  }

  //Check if the handbits matches any known straight
  for (int i = 0; i < STRAIGHT_COUNT; ++i)
  {
    if ((handbits & BIT_MASKS[i]) == BIT_MASKS[i])
    {
      return 1;
    }
  }
  return 0;

#elif defined(OptimizedSTD)
  
  //set bits
  BitwiseHand.reset();
  for (int i = 0; i < 5; i++)
  {
    
    BitwiseHand.set(k[i]-2);
  }

  if ( HandLookUp.contains(BitwiseHand) )
  {
    return 1;
  }
  
  BitwiseHand.reset();
  return 0;

  #elif defined(OptimizedNot)

  std::sort(k, k + 5);

  // Check for Ace-low straight (A-2-3-4-5)
  if (k[0] == 2 && k[1] == 3 && k[2] == 4 && k[3] == 5 && k[4] == 14)
  {
    return 1;
  }

  // Check for a normal straight
  for (int i = 1; i < 5; ++i)
  {
    if (k[i] != k[i - 1] + 1)
    {
      return 0;
    }
  }

  return 1;

  #endif

}

inline void is_quadsorfullhouse(int *k, int& y, int& j)
{

  #if defined(OptimizedNot)

  int cards[13] {0};
  bool twoof = 0;
  bool threeof = 0;
  std::sort(k, k + 5);

  for (int i = 0; i < 5; i++)
  {
    cards[(k[i] - 2)] += 1;
  }

  for (int i = 0; i < 13; i++)
  {
    if ( cards[i] == 4)
    {
      ++y;
    }

    if ( cards[i] == 2)
    {
      twoof = 1;
    }

    if ( cards[i] == 3)
    {
      threeof = 1;
    }
  }

  if (twoof && threeof)
  {
    ++j;
  }

  #elif defined(OptimizedRaw)



  #endif

}