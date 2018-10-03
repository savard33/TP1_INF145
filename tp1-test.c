#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

#include "op_bits.h"


typedef unsigned int uint;

#define TEST 1
#define SIM  0

#define MAX_CHAINE 10
#define MIN_CHAINE 4

#define MAX_PROD 10
#define MIN_PROD 5

#define MAX_PROB_BRIS 1
#define MIN_PROB_BRIS 0


/*recoit une valeur max et min et retourne un integer si la valeur et entre les limites*/
int get_int(int MAX, int MIN);     

/*recoit une valeur max et min et retourne un double si la valeur et entre les limites*/
double get_double(int MAX, int MIN); 

/*mets à 1 les equipements utilisé*/
uint configuration_intiale(int nb_total_equipe); 

//retourne 1 si la chaine testé n'a pas d'équipements brisé et sinon 0
int chaine_est_rentable(uint equips, int num_chaine, int nb_eq_chaine);

#if (SIM)  si vrai on utilise le code normal du main
int main(void)pemnt
{
	int nb_eq_chaine;
	int prod_chaine;
	double prob_bris_eq;

	printf("\n Nombre d'equipements dans une chaine" );
		nb_eq_chaine = get_int(MAX_CHAINE, MIN_CHAINE);
	printf("nb = %d \n", nb_eq_chaine);

	printf("\n Porduction quotidienne d'une chaine" );
		prod_chaine = get_int(MAX_PROD, MIN_PROD);
	printf("nb = %d \n", prod_chaine);

	printf("\n Probabilite de bris d'equipement" );
		prob_bris_eq = get_double(MAX_PROB_BRIS, MIN_PROB_BRIS);
	printf("\nb = %lf \n", prob_bris_eq);

	system("pause");
}
#endif


#if(TEST)  //si vrai un test les sous-programmes 

void test_configuration_initiale(void);

int main(void)
{
	
	test_configuration_initiale();
	system("pause");
	return EXIT_SUCCESS;

}
#endif


//Cette implémentation est non - fonctionnelle!!!

uint configuration_initiale(int nb_equipements)
{
	return (0x00000000 | 0xFF000000);
}

void test_configuration_initiale(void)
{
	int rentable;

	uint test1 = configuration_intiale(8);
	uint test2 = configuration_intiale(1);
	uint test3 = configuration_intiale(32);
	


	printf("TEST_CONFIGURATION_INITIALE");
	printf("\nTEST1");
	printf("\ntValeur voulue  %s", bits2string(0xFF000000));
	printf("\ntValeur obtenu  %s", bits2string(test1));
	
	printf("\nTEST2");
	printf("\ntValeur voulue  %s", bits2string(0x80000000));
	printf("\ntValeur obtenu  %s", bits2string(test2));

	printf("\nTEST3");
	printf("\ntValeur voulue  %s", bits2string(0xFFFFFFFF));
	printf("\ntValeur obtenu  %s", bits2string(test3));
	printf("\ntValeur obtenu  %i", test3/8);

	rentable = chaine_est_rentable(test1,1,4);

	printf("\n rentabilite %i", rentable);

	printf("\n\n\n");



}




//Cette fonction recoit les valeurs maximum et minimum et retourne un int
//si la valeurs est entre les bornes maximum et minimum.

int get_int(int MAX, int MIN)
{
	int nb;
	scanf("%d", &nb);
	while (nb > MAX && nb < MIN)
	{
		printf("\n la valeur n'est pas valide, entrez une autre valeur entre %d et %d" , MIN,MAX);
			scanf("%d", &nb);

	}
	return nb;

}



//Cette fonction recoit les valeurs maximum et minimum et retourne un double
//si la valeurs est entre les bornes maximum et plus grand que la valeur minimum.

double get_double(int MAX, int MIN)
{
	double nb;
	scanf("%lf", &nb);
	while (nb > MAX || nb <= MIN)
	{
		printf("/n la valeur n'est pas valide entrer une autre valeur entre %d et et plus grand que %d" , MAX,MIN);
			scanf("%lf", &nb);

	}
	return nb;
}


/*
stratégie:	un itérateur et égale 32 - le nombre total d'equipement. 
			Ex: 32-8=24 donc l'itérateur vas ce prositoner sur le 24ème bit.
			Ceci nous permet de ce postioner sur le bit significatif voulue.

			Tant que le i<32 on mets le bit désiré à 1 ensuite on incrémente
			l'itérateur.

			Quand le i est = ou plus grand que 32 on retourne la valeur du
			unsigned integer.
*/
uint configuration_intiale(int nb_total_equipe)
{
	int i;							// itérateur
	uint usine = 0;					// unsigned integer qui représente l'usine
	i = 32 - nb_total_equipe;		// initialise le i avec la position du bit de commencement sur 32 bits
	while (i<32)
	{
		usine = set_bit(usine, i);  // mets les bits à 1
		i++;						// incrémente l'itérateur 
	}
	return usine;

}

/*
	stratégie:	on utilise la formule pos_total=32-1-(num_chaine*nb_eq_equip+pos_chaine)
				on définie un compteur qui est initialement à 0. 

				tant que le compteur est plus petit que nb_eq_chaine on rentre dans la boucle.
				on test si le bit est égale à 0 avec la fonction get_bit.
				
				si il est égale à 0 on met un int nommé rentable à 0 et on sort de la boucle while.

				si il n'est pas égale à 0 rentable == 1. une fois que la boucle while est terminé on retourne
				rentable.

*/	
int chaine_est_rentable(uint equips, int num_chaine, int nb_eq_chaine)
{
	int pos;
	int compt=0;
	int rentable;
	int i = 0;
	int bit_pos;

	pos = 32 - 1 - (num_chaine*nb_eq_chaine + i);

	printf("\n pos = %d", pos);

	while (compt < nb_eq_chaine)
	{
		bit_pos = get_bit(equips, pos);

		if (bit_pos==0)
		{
			rentable = 0;
			compt = nb_eq_chaine;
		}
		else
		{
			rentable = 1;
			compt++;
			pos--;
		}
	}

	return rentable;


}
