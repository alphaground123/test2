/*****************************************************/
/*         MiniProjet d'Algorithmique Avancee        */
/*        Sujet 22 : Operations sur Polynomes        */
/*   Realise par Antonin MENEGAUX et Mehdi BAROUTI   */
/*      Eleves de Polytech'Paris-UPMC ELI3 GR1       */
/*                                                   */
/*      http://polynomproject.googlepages.com        */
/*                                                   */
/*****************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "polynom.h"





/*********************************************************/
/*                 FONCTION CREATIONMONOME               */
/*                                                       */
/*********************************************************/

/*                   Cree un monome                      */
polynome* CreationMonome (double coefficient, long exposant){

  polynome *monome;
  monome = (polynome *) malloc (sizeof (polynome));

  monome->Coeff = coefficient;
  monome->Deg = exposant;
  monome->Suiv = NULL;

  return monome;
}

/*********************************************************/
/*             FONCTION LIBERERPOLYNOME                  */
/*                                                       */
/*********************************************************/

/*    Libere la memoire occupee par tout un polynome     */
void LibererPolynome (polynome * P){

  polynome *suivant;

  while (P != NULL){
    suivant = P->Suiv;             /* On sauvegarde le monome suivant */
    P->Suiv = NULL;
    free (P);                      /* On libere la memoire du monome */
    P = suivant;                   /* On passe au suivant */
  }
}

/*********************************************************/
/*              FONCTION STRINGOFMONOME                  */
/*                                                       */
/*********************************************************/
char* StringOfMonome (polynome * monome){

  char *monomestring;
  monomestring = (char *) malloc (512 * sizeof (char));

                                                                                 /* Differents cas pour la representation en chaine de cractere d'un monome */
  if (monome->Coeff == 0){
    sprintf (monomestring, "0");
  }
  else if (monome->Deg == 0){                                                    /* Le degre est egal a 0 => On affiche que le coefficient */
    sprintf (monomestring, "%f", fabs(monome->Coeff));
  }
  else if (monome->Deg == 1){                                                    /* Le degre est egal a 1 => On affiche que le coefficient suivit de la variable "x" */
    if (monome->Coeff == 1 || monome->Coeff == -1){                              /* Si le coefficient est egal a 1 on ne l'affiche pas */
      sprintf (monomestring, "x");
    }
    else{
      sprintf (monomestring, "%fx", fabs(monome->Coeff));
    }
  }
  else{
    if(monome->Coeff == 1 || monome->Coeff == -1){                               /* Si le coefficient est egal a 1 on ne l'affiche pas */
      sprintf (monomestring, "x^%lu", monome->Deg);
    }
    else sprintf (monomestring, "%fx^%lu", fabs(monome->Coeff), monome->Deg);    /* Cas le plus general => on affiche tout */
  }

  return monomestring;
}

/*********************************************************/
/*               FONCTION AFFICHERPOLYNOME               */
/*                                                       */
/*********************************************************/
void AfficherPolynome (polynome * P){

  polynome *Parcours = P;
  char *StringMonomeTemp;

  if (P == NULL) printf ("0\n");
  else{
    while (Parcours != NULL){
      StringMonomeTemp = StringOfMonome (Parcours);           /* On appel la fonction StringOfMonome */
      if (Parcours->Coeff < 0){                               /* Si le coefficient est negatif on affiche un "-" devant */
	if (Parcours == P) printf ("-%s ", StringMonomeTemp);
	else printf ("- %s ", StringMonomeTemp);
      }
      else{                                                   /* Si le coefficient est positif on affiche un "+" devant */
	if (Parcours == P) printf ("%s ", StringMonomeTemp);
	else printf ("+ %s ", StringMonomeTemp);
      }
      Parcours = Parcours->Suiv;                              /* On passe au monome suivant */
      free (StringMonomeTemp);                                /* On libere la memoire de la chaine de caractere correspondante a chaque fois */
    }
    
    printf ("\n");
  }
}

/*********************************************************/
/*            FONCTION ENREGISTRERPOLYNOME               */
/*                                                       */
/*********************************************************/
void EnregistrerPolynome (polynome * P){

  FILE* Fichier;
  polynome *Parcours = P;
  char *StringMonomeTemp;

  Fichier = fopen("polynomeResult","a");                      /* On ouvre le fichier en écriture en se placant a la fin de celui ci */
  if(Fichier == NULL){                                        /* Cas d'erreur de l'ouverture ou de la creation du fichier */
    fprintf (stderr,"---ERREUR--- Echec de l'ouverture du fichier polynomResult\n");
    exit (EXIT_FAILURE);
  }

  if (P == NULL){
    fprintf (Fichier, "0\n\n");
  }
  else{
    while (Parcours != NULL){
      StringMonomeTemp = StringOfMonome (Parcours);           /* On appel la fonction StringOfMonome */
      if (Parcours->Coeff < 0){                               /* Si le coefficient est negatif on ecrit un "-" devant */
	if (Parcours == P) fprintf (Fichier, "-%s ", StringMonomeTemp);
	else fprintf (Fichier, "- %s ", StringMonomeTemp);
      }
      else{                                                   /* Si le coefficient est positif on ecrit un "+" devant */
	if (Parcours == P) fprintf (Fichier, "%s ", StringMonomeTemp);
	else fprintf (Fichier, "+ %s ", StringMonomeTemp);
      }
      Parcours = Parcours->Suiv;                              /* On passe au monome suivant */
      free (StringMonomeTemp);                                /* On libere la memoire de la chaine de caractere correspondante a chaque fois */
    }

    fprintf (Fichier, "\n\n");
  }

  fclose(Fichier);
}

/*********************************************************/
/*            FONCTION CONSTRUCTIONPOLYNOME              */
/*                                                       */
/*********************************************************/
polynome* ConstructionPolynome (FILE* fichier){

  char *stringcoef, *stringexpo, *Poly;
  int x, c, e, creer, fin;
  /* x indique si l'on a rencontre un "x"(x=1) ou un "^"(x=2) */
  /* c et e servent a avancer dans les variables coefficient et exposant */
  /* creer vaut 1 lorsque l'on a capture la totalite d'un monome */
  /* fin indique si l'on est arrivee a la fin d'une ligne dans le fichier */
  double coefficient;
  long exposant;
  polynome *Creation, *Polynome;

  Poly = (char *) malloc (sizeof (char));
  stringcoef = (char *) malloc (128 * sizeof (char));
  stringexpo = (char *) malloc (128 * sizeof (char));
  x = c = e = creer = fin = 0;
  Polynome = Creation = NULL;

  fgets(Poly,2,fichier); /* On recopie un caractere pointe par Fichier dans la variable Poly, le pointeur Fichier pointe ensuite sur le caractere suivant */

  while(Poly[0]=='\n' || Poly[0]==' ' || feof(fichier)){ /* Cette premiere boucle sert a avancer dans le fichier tant qu'il y a des espaces ou des retours chariots */
    if (feof(fichier)){ /* Si l'on est a la fin du fichier alors il n'y a pas de polynomes dans celui ci */
      fprintf (stderr,"---ERREUR--- Absence d'un ou plusieurs polynomes dans le fichier\n");
      exit (EXIT_FAILURE);
    }
    else{
      fgets(Poly,2,fichier);
    }
  }

  while (fin==0 || creer==1){
    if (creer == 1){                       /* Cas ou l'on creer un monome */
      coefficient = atof (stringcoef);     /* On convertit la chaine de caractere stringcoef en double */
      exposant = atol (stringexpo);        /* On convertit la chaine de caractere stringexpo en long */
      c = e = x = creer = 0;               /* On remet a zero les variables servant a la capture d'un monome */
      if (Polynome == NULL){               /* C'est le premier monome que l'on creer, on sauvegarde la tete du polynome dans la variable Polynome */
	Creation = CreationMonome (coefficient, exposant);
	Polynome = Creation;
      }
      else{                                /* Sinon on realise le chainage du polynome */
	if (exposant >= Creation->Deg){    /* On verifie que les polynomes sont ecrit par ordre decroissant d'exposants */
	  fprintf (stderr,"---ERREUR--- Les polynomes ne sont pas ecrits par ordre decroissant d'exposants\n");
	  exit (EXIT_FAILURE);
	}
	else{
	  Creation->Suiv = CreationMonome (coefficient, exposant);
	  Creation = Creation->Suiv;
	}
      }
    }
    else{
      if (x == 0){   /* x=0, on est en train de capturer le coefficient */
         /* Plusieurs cas on fonction de la nature du caractere */
	if (Poly[0] == 'x'){ /* On rencontre un "x", on a fini de capturer le coefficient */
	  if (c == 0){ /* Il n'y avait aucun caractere correspondant au coefficient => le seul cas possible est celui ou l'on capture le premier monome */
	    if (Polynome == NULL){
	      stringcoef[0] = '1';
	      stringcoef[1] = '\0';
	    }
	    else{
	      fprintf (stderr,"---ERREUR--- Mauvais format pour le polynome au niveau du caractere: '%c'\n>>>>>>>>>>>> Attente d'un operateur '+' ou '-'\n",Poly[0]);
	      exit (EXIT_FAILURE);
	    }
	  }
	  else if (c==1){ /* Si c=1, et que le coefficient n'est que constitue d'un signe, c'est que le coefficient =1 */
	    if ( stringcoef[0] == '+' || stringcoef[0] == '-'){
	      stringcoef[1] = '1';
	      stringcoef[2] = '\0';
	    }
	  }
	  else{ /* Dans le cas general on indique la fin du coefficient dans la variable stringcoef */
	    stringcoef[c] = '\0';
	  }
	  fgets(Poly,2,fichier);
	  x = 1;
	}
	else if (Poly[0] == ' '){
	  if (c==0 || (c==1 && (stringcoef[0]=='+' || stringcoef[0]=='-'))){ /* Cas ou il y a des espaces apres les signes des monomes ou entre deux monomes => On avance dans le fichier */
	    fgets(Poly,2,fichier);
	  }
	  else{/* Sinon c'est que l'on a rencontre une constante sans terme en x, on a fini de capturer le coefficient et l'exposant vaut 0 */
	    creer = 1;
	    stringcoef[c] = '\0';
	    stringexpo[0] = '0';
	    stringexpo[1] = '\0';
	  }
	}else if (Poly[0]=='+' || Poly[0]=='-'){
	  if (c == 0){/* Cas ou on rencontre le signe du monome, on le capture et on passe au caractere suivant dans le fichier */
	    stringcoef[c] = Poly[0];
	    c++;
	    fgets(Poly,2,fichier);
	  }
	  else if (c == 1){ /* Cas d'erreur ou l'utilisateur a saisi deux operateurs a la suite */
	    fprintf (stderr,"---ERREUR--- Mauvais format pour le polynome:\n>>>>>>>>>>>> Il y a deux operateurs a la suite\n");
	    exit (EXIT_FAILURE);
	  }
	  else{/* Sinon c'est que l'on a rencontre une constante sans terme en x, on a fini de capturer le coefficient et l'exposant vaut 0 */
	    creer = 1;
	    stringcoef[c] = '\0';
	    stringexpo[0] = '0';
	    stringexpo[1] = '\0';
	  }
	}
	else if (Poly[0]>='0' && Poly[0]<='9'){
	  if (c==0 && Polynome!=NULL){ /* C'est le cas ou il manque le signe entre deux monome */
	    fprintf (stderr,"---ERREUR--- Mauvais format pour le polynome au niveau du caractere: '%c'\n>>>>>>>>>>>> Attente d'un operateur '+' ou '-'\n",Poly[0]);
	    exit (EXIT_FAILURE);
	  }
	  else{ /* Sinon on est dans le cas general on capture un chiffre du coefficinet et on avance dans le fichier */
	    stringcoef[c] = Poly[0];
	    c++;
	    fgets(Poly,2,fichier);
	  }
	}
	else if (Poly[0]=='.'){
	  if (c==0 && Polynome!=NULL){ /* C'est le cas ou il manque le signe entre deux monome */
	    fprintf (stderr,"---ERREUR--- Mauvais format pour le polynome au niveau du caractere: '%c'\n>>>>>>>>>>>> Attente d'un operateur '+' ou '-'\n",Poly[0]);
	    exit (EXIT_FAILURE);
	  }
	  else{
	    stringcoef[c] = Poly[0];
	    c++;
	    fgets(Poly,2,fichier);
	  }
	}
	else{ /* Si le caractere ne correspond a aucun des tests precedents il n'est pas reconnu */
	  fprintf (stderr,"---ERREUR--- Probleme de lecture du polynome\n>>>>>>>>>>>> Le caractere: '%c' n'est pas reconnu\n",Poly[0]);
	  exit (EXIT_FAILURE);
	}
      }
      else if (x == 1){ /* x=1 => cas ou l'on vient de rencontrer un "x" et que l'on est positionne apres */
	if (Poly[0] == '^'){ /* Cas ou il y a un exposant, on le capture */
	  fgets(Poly,2,fichier);
	  x = 2;
	}
	else if (Poly[0] == ' ' || Poly[0] == '+' || Poly[0] == '-'){ /* Cas ou il n'y a pas d'exposant, l'exposant vaut alors 1 */
	  creer = 1;
	  stringexpo[0] = '1';
	  stringexpo[1] = '\0';
	}
	else if (Poly[0] >= '0' && Poly[0] <= '9'){ /* Si l'utilisateur n'a pas ecrit le "^" apres la variable "x" */
	  fprintf (stderr,"---ERREUR--- Mauvais format pour le polynome au niveau du caractere: '%c'\n>>>>>>>>>>>> Attente du caractere '^' apres le 'x'\n",Poly[0]);
	  exit (EXIT_FAILURE);
	}
	else{ /* Si le caractere ne correspond a aucun des tests precedents il n'est pas reconnu */
	  fprintf (stderr,"---ERREUR--- Mauvais format pour le polynome:\n>>>>>>>>>>>> Le caractere: '%c' n'est pas reconnu\n",Poly[0]);
	  exit (EXIT_FAILURE);
	}
      }else if (x == 2){ /* x=2 => on est en train de capturer l'exposant */
	if (Poly[0] == ' ' || Poly[0] == '+' || Poly[0] == '-'){
	  if (e == 0){ /* S'il n'y a pas d'exposant apres le "^" */
	    fprintf (stderr,"---ERREUR--- Mauvais format pour le polynome:\n>>>>>>>>>>>> Attente d'un exposant apres '^' au niveau du caractere: '%c'\n",Poly[0]);
	    exit (EXIT_FAILURE);
	  }
	  else{ /* On a capturer tout l'exposant, la capture du monome est alors termine, il faut le creer */
	    creer = 1;
	    stringexpo[e] = '\0';
	  }
	}
	else if (Poly[0] >= '0' && Poly[0] <= '9'){ /* Cas general ou l'on capture l'exposant */
	  stringexpo[e] = Poly[0];
	  e++;
	  fgets(Poly,2,fichier);
	}
	else{/* Si le caractere ne correspond a aucun des tests precedents il n'est pas reconnu */
	  fprintf (stderr,"---ERREUR--- Mauvais format pour le polynome:\n>>>>>>>>>>>> Le caractere: '%c' n'est pas reconnu\n",Poly[0]);
	  exit (EXIT_FAILURE);
	}
      }
    }
    if (Poly[0]=='\n' || feof(fichier)){ /* On test a chaque fois si l'on a atteint la fin de la ligne ou du fichier */
      fin = 1; /* fin=1 => on a atteint la fin d'une ligne */
      if (c != 0 || e != 0){ /* Si on etait en train de capturer un monome */
	creer = 1; /* On devra alors creer ce drenier monome */
	/* Different en fonction de la varaible x */
	if (x==0){
	  stringcoef[c] = '\0';
	  stringexpo[0] = '\0';
	}
	else if (x==1){
	  stringexpo[0] = '1';
	  stringexpo[1] = '\0';
	}
	else stringexpo[e] = '\0';
      }
    }
  }
  
  free(stringexpo); /* On libere la memoire des 2 chaines de caracteres utilisees */
  free(stringcoef);
  return Polynome;
}

/*********************************************************/
/*                  FONCTION ADDITION                    */
/*                                                       */
/*********************************************************/
polynome* Addition(polynome* P1, polynome* P2){
  polynome *P3,*PC,*DEL;
  P3 = PC = NULL;
  
  while(P1!=NULL || P2!=NULL){
    if(PC == NULL){               /* Si PC vaut NULL c'est qu'il n'est pas place */
      if(P1 == NULL) return P2;   /* Si un des 2 polynomes est NULL on renvoi l'autre */
      if(P2 == NULL) return P1;
      if(P1->Deg > P2->Deg){      /* On place le pointeur courant PC sur le monome de plus grand exposant, ici P1 */
	P3 = P1;                  /* On sauvegarde alors la tete du resultat de l'addition dans P3 */
	P1 = P1->Suiv;            /* Le pointeur courant de P1 passe au monome suivant */
	PC = P3;
      }else if(P1->Deg < P2->Deg){/* On place le pointeur courant PC sur le monome de plus grand exposant, ici P1 */
	P3 = P2;                  /* On sauvegarde alors la tete du resultat de l'addition dans P3 */
	P2 = P2->Suiv;            /* Le pointeur courant de P2 passe au monome suivant */
	PC = P3;
      }else if(P1->Coeff == -P2->Coeff){ /* Cas ou les deux monomes s'annulent => PC ne peut pas etre positionne */
	DEL = P1;                        /* On sauvegarde le monome a supprimer dans P1 */
	P1 = P1->Suiv;                   /* Le pointeur courant de P1 avance au monome suivant */
	free(DEL);                       /* On libere la memoire du monome */
	DEL = P2;                        /* On sauvegarde le monome a supprimer dans P2 */
	P2 = P2->Suiv;                   /* Le pointeur courant de P2 avance au monome suivant */
	free(DEL);                       /* On libere la memoire du monome */
      }else{                     /* Cas ou les degres des 2 monomes sont egaux => On supprime alors arbitrairement un monome de P2 et PC ne peut pas etre positionne*/
	P1->Coeff += P2->Coeff;  /* On additionne alors les coefficients dans le monome pointe par P1 */
	DEL = P2;                /* On sauvegarde le monome a supprimer dans P2 */
	P2 = P2->Suiv;           /* Le pointeur courant de P2 avance au monome suivant */
	free(DEL);               /* On libere la memoire du monome */
      }
    }else{                /* Le pointezur courant PC a deja ete positionne */
      if(P1 == NULL){     /* Si le pointeur courant dans P1 est NULL alors il faut chainer PC au pointeur courant de P2 */
	PC->Suiv = P2;    /* Dernier chainage */
	P2 = NULL;        /* Cas d'arret de la boucle */
      }else if(P2 == NULL){ /* Si le pointeur courant dans P2 est NULL alors il faut chainer PC au pointeur courant de P1 */
	PC->Suiv = P1;      /* Dernier chainage */
	P1 = NULL;          /* Cas d'arret de la boucle */
      }else if(P1->Deg > P2->Deg){ /* Si le degre de P1 est superieur a P2 on chaine alors le polynome sur P1 */
	PC->Suiv = P1;             /* On realise le chainage */
	PC = P1;                   /* PC pointe alors sur le plus grand des 2 monomes */
	P1 = P1->Suiv;             /* Le pointeur courant de P1 avance au monome suivant */
      }else if(P1->Deg < P2->Deg){ /* Si le degre de P2 est superieur a P1 on chaine alors le polynome sur P2 */
	PC->Suiv = P2;             /* On realise le chainage */
	PC = P2;                   /* PC pointe alors sur le plus grand des 2 monomes */
	P2 = P2->Suiv;             /* Le pointeur courant de P2 avance au monome suivant */
      }else if(P1->Coeff == -P2->Coeff){ /* Cas ou les deux monomes s'annulent */
	DEL = P1;                        /* On sauvegarde le monome a supprimer dans P1 */
	P1 = P1->Suiv;                   /* Le pointeur courant de P1 avance au monome suivant */
	free(DEL);                       /* On libere la memoire du monome */
	DEL = P2;                        /* On sauvegarde le monome a supprimer dans P2 */
	P2 = P2->Suiv;                   /* Le pointeur courant de P2 avance au monome suivant */
	free(DEL);                       /* On libere la memoire du monome */
	if(P1==NULL && P2==NULL) PC->Suiv = NULL; /* S'il n'a y a plus de monomes dans P1 et P2 le suiant de PC prend la valeur NULL */
      }else{                                      /* Cas ou les degres des 2 monomes sont egaux => On supprime alors arbitrairement un monome de P2 */
	P1->Coeff += P2->Coeff;                   /* On additionne alors les coefficients dans le monome pointe par P1 */
	DEL = P2;                                 /* On sauvegarde le monome a supprimer dans P2 */
	P2 = P2->Suiv;                            /* Le pointeur courant de P2 avance au monome suivant */
	free(DEL);                                /* On libere la memoire du monome */
      }
    }
  }

  return P3;
}

/*********************************************************/
/*                 FONCTION SOUSTRACTION                 */
/*                                                       */
/*********************************************************/
polynome* Soustraction(polynome* P1, polynome* P2)
{
  polynome *parcoursP2 = P2;

  while (parcoursP2 != NULL){
    parcoursP2->Coeff = -parcoursP2->Coeff;  /* On inverse le signe du monome courant */
    parcoursP2 = parcoursP2->Suiv;           /* On passe au monome suivant */
  }

  return Addition(P1,P2);                    /* On utilise alors la fonction Addition afin de renvoyer Addition(P1,-P2) */
}

/*********************************************************/
/*                 FONCTION COPIERPOLYNOME               */
/*                                                       */
/*********************************************************/
polynome* CopierPolynome(polynome* P){
  polynome *parcours,*copie,*tetecopie;
  parcours = P;

  if(P == NULL) return NULL;                              /* Si le polynome a copier vaut NULL on renvoi NULL */

  copie = CreationMonome(parcours->Coeff,parcours->Deg);  /* On copie le 1er monome de P */
  parcours = parcours->Suiv;                              /* On passe au deuxieme monome de P */
  tetecopie = copie;                                      /* On sauvegarde la tete de la copie */

  while(parcours != NULL){
    copie->Suiv = CreationMonome(parcours->Coeff,parcours->Deg); /* On copie le monome courant et on realise le chainage */
    copie = copie->Suiv;
    parcours = parcours->Suiv;                                   /* On passe au monome suivant de P */
  }

  return tetecopie;
}

/*********************************************************/
/*         FONCTION MULTIPLICATIONCONSERVATRICE          */
/*                                                       */
/*********************************************************/
polynome* MultiplicationConservatrice(polynome* P, polynome* monome){
  polynome *parcours,*res,*PM;
parcours = P;

  if (P==NULL || monome==NULL) return NULL;

  res = CreationMonome(parcours->Coeff*monome->Coeff,parcours->Deg+monome->Deg); /* On multiplie le 1er monome de P1 */
  parcours = parcours->Suiv;
  PM = res;                                                                      /* On sauvegarde la tete de la multiplication */

  while(parcours != NULL){
    res->Suiv = CreationMonome(parcours->Coeff*monome->Coeff,parcours->Deg+monome->Deg); /* On multiplie le monome courant et on realise le chainage */
    res = res->Suiv;
    parcours = parcours->Suiv;                                                           /* On passe au monome suivant de P */
  }

  return PM;
}

/*********************************************************/
/*                   FONCTION DIVISION                   */
/*                                                       */
/*********************************************************/
polynome** Division (polynome *P1,polynome *P2)
{
polynome *monomediv, *polysoustrait;
  polynome** TABQR = (polynome**)malloc(2*sizeof(polynome*));
  TABQR[0] = TABQR[1] = NULL;

  if (P1 == NULL) return NULL; /* On divise 0, le resultat est alors 0 */

  if (P2==NULL || P2->Coeff==0){
    fprintf (stderr,"---ERREUR--- Division par 0\n");
    exit (EXIT_FAILURE);
  }
  if (P1->Deg < P2->Deg){      /* On ne peut appliquer la division Euclidienne =>   P1 = 0*P2 + P1 */
    TABQR[1] = P1;
    TABQR[0] = NULL;
    LibererPolynome(P2);
    return TABQR;
  }
  if (P2->Suiv == NULL){       /* Division par un monome */
    TABQR[1] = NULL;
    TABQR[0] = P1;
    while(P1 != NULL){         /* On divise chaque monome du polynome divise par p2 */
      if (P1->Deg < P2->Deg){  /* Si la division fait apparaitre un signe negatif on genere une erreur */
	fprintf (stderr,"---ERREUR--- La division de p1 par p2 fait apparaitre un exposant negatif\n");
	exit (EXIT_FAILURE);
      }
      P1->Coeff /= P2->Coeff;
      P1->Deg -= P2->Deg;
      P1 = P1->Suiv;
    }
    LibererPolynome(P2);        /* On libere la memoire du monome P2 */
    return TABQR;
  }

  TABQR[1]=P1;                  /* Au debut le Reste vaut P1*/
  while (TABQR[1] != NULL && (TABQR[1]->Deg >= P2->Deg)){ /* Tant que le Reste n'est pas nul, ou tant que le Reste a un degre superieur au diviseur P2 */

    monomediv = CreationMonome(TABQR[1]->Coeff / P2->Coeff, TABQR[1]->Deg - P2->Deg); /* On calcul directement le monome qui divise le Reste */

    polysoustrait = MultiplicationConservatrice(P2,monomediv); /* polysoustrait sera soustrait au Reste, il correspond a la multiplication de monomediv avec P2 */
    /* P2 est intact car on le réutilise a chaque passage dans la boucle */

    TABQR[0] = Addition(TABQR[0],monomediv); /* On ajoute le monome diviseur au Quotient */

    TABQR[1] = Soustraction(TABQR[1],polysoustrait); /* On soustrait au Reste polysoustrait selon l'algorithme de division Euclidienne */
  }
  LibererPolynome(P2); /* On libere la memoire de P2 */
  return TABQR;
}



/*********************************************************/
/*           FONCTION MULTIPLICATIONINTELLIGENTE         */
/*                                                       */
/*********************************************************/

/* Multiplie deux polynomes de degres au plus egaux à 1  */

polynome* MultiplicationIntelligente(polynome* P1, polynome* P2){
  double m,n,p; /* seront utilises pour le premier cas, pour optimiser la multiplication */
  polynome* P; /* polynome qui sera retourne */
  
  if (P1==NULL || P2==NULL) return NULL;    /* toute multiplication par un polynome nul, retourne un polynome nul */
  
  if( (*P1).Deg > 1 || (*P2).Deg > 1 ){
    fprintf(stderr,"---ERREUR--- Dans la fonction MultiplicationIntelligente, erreur sur le degre d'un des arguments\n");
    exit(EXIT_FAILURE);
  }
  else if( ((*P1).Deg == 1) && ((*P2).Deg == 1)  && (*P1).Suiv != NULL && (*P2).Suiv != NULL ){     /* P1 = aX + b; P2 = cX + d */
    m = ( ((*P1).Coeff) + ( (*(*P1).Suiv).Coeff) )*( ((*P2).Coeff) + ((*(*P2).Suiv).Coeff) );       /* m = (a+b)(c+d) */
    n = ((*P1).Coeff)*((*P2).Coeff);                                                                /* n = ac */
    p = ((*(*P1).Suiv).Coeff)*((*(*P2).Suiv).Coeff);                                                /* p = bd */
    P = CreationMonome(n,2);                                                                        /* P = nX^2 */
    (*P).Suiv = CreationMonome(m-n-p,1);                                                            /* P = nX^2 + (m-n-p)X */
    (*(*P).Suiv).Suiv = CreationMonome(p,0);                                                        /* P = nX^2 + (m-n-p)X + p */
    (*(*(*P).Suiv).Suiv).Suiv = NULL;                                                               /* multiplication realisee avec 3 produits au lieu de 4 */
  }
  else if( ((*P1).Deg == 1) && ((*P1).Suiv == NULL) && P2 != NULL && (*P2).Suiv != NULL ){          /* P1 = aX; P2 = cX + d */
    P = CreationMonome(((*P1).Coeff)*((*P2).Coeff),2);                                              /* P = acX^2 */
    (*P).Suiv = CreationMonome(((*P1).Coeff)*((*(*P2).Suiv).Coeff),1);                              /* P = acX^2 + adX */
    (*(*P).Suiv).Suiv = NULL;
  }
  else if( ((*P1).Deg == 0) && ((*P2).Deg == 1) && ((*P2).Suiv != NULL) ){                          /* P1 = b; P2 = cX + d */
    P = CreationMonome(((*P1).Coeff)*((*P2).Coeff),1);                                              /* P = bcX */
    (*P).Suiv = CreationMonome(((*P1).Coeff)*((*(*P2).Suiv).Coeff),0);                              /* P = bcX +bd */
    (*(*P).Suiv).Suiv = NULL;
  }
  else if( ((*P2).Deg == 1) && ((*P2).Suiv == NULL) && P1 != NULL && (*P1).Suiv != NULL ){          /* P1 = aX + b; P2 = cX */
    P = MultiplicationIntelligente(P2,P1);                                                          /* On rapelle le cas symetrique */
  }
  else if( ((*P1).Deg == 1) && ((*P1).Suiv == NULL) && ((*P2).Deg == 1) && ((*P2).Suiv == NULL)){   /* P1 = aX; P2 = cX */
    P = CreationMonome(((*P1).Coeff)*((*P2).Coeff),2);                                              /* P = acX^2 */
    (*P).Suiv = NULL;
  }
  else if( ((*P1).Deg == 0) && ((*P2).Deg == 1) && ((*P2).Suiv == NULL)){                           /* P1 = b; P2 = cX */
    P = CreationMonome(((*P1).Coeff)*((*P2).Coeff),1);                                              /* P = bcX */
    (*P).Suiv = NULL;
  }
  else if( ((*P2).Deg == 0) && ((*P1).Deg == 1) && ((*P1).Suiv != NULL) ){                          /* P1 = aX + b; P2 = d */
    P = MultiplicationIntelligente(P2,P1);                                                          /* On rapelle le cas symetrique */
  }
  else if( ((*P2).Deg == 0) && ((*P1).Deg == 1) && ((*P1).Suiv == NULL)){                           /* P1 = aX; P2 = d */
    P = MultiplicationIntelligente(P2,P1);                                                          /* On rapelle le cas symetrique */
  }
  else if( ((*P1).Deg == 0) && ((*P2).Deg == 0)){                                                   /* P1 = b; P2 = d */
    P = CreationMonome(((*P1).Coeff)*((*P2).Coeff),0);                                              /* P = bd */
    (*P).Suiv = NULL;
  }
  else{
    fprintf(stderr,"Erreur : Aucun cas ne correspond\n");
    exit(EXIT_FAILURE);
  }
  return P;
}
  

/*********************************************************/
/*              FONCTION MULTIPLIERKARATSUBA             */
/*                                                       */
/*********************************************************/

/* Multiplie deux polynomes de degres egaux selon l'algorithme Karatsuba */
polynome* MultiplicationKaratsuba(polynome* P1, polynome* P2){

  polynome *PC1,*PRECPC1,*PC2,*PRECPC2,*M,*N,*O,*P,*Q,*R,*S,*T,*U,*V;
  int D;

  if (P1==NULL || P2==NULL) return NULL;   /* toute multiplication par un polynome nul, retourne un polynome nul */

  /*if((*P1).Deg != (*P2).Deg){
    fprintf(stderr, "Erreur : Degres differents dans Karatsuba\n");
    exit(EXIT_FAILURE);
    }*/

  if( ((*P1).Deg <= 1) && ((*P2).Deg <= 1)){  /* Si les polynomes sont de degres au plus 1 */
    return MultiplicationIntelligente(P1,P2); /* On apelle multiplication Intelligente */
  }
  else{
    PC1 = P1;
    PC2 = P2;
    D = (int)((*P1).Deg)/2; /* D = partie entiere inferieur du degre */

    while(PC1!=NULL && (*PC1).Deg > D){ /* PC1 parcours P1 jusqu'au degre D */
      (*PC1).Deg -= (D+1);              /* les degres sont baisses */
      PRECPC1 = PC1;                    /* PRECPC1 est le precedent de PC1 */
      if((*PC1).Suiv != NULL){
	PC1 = (*PC1).Suiv;
      }
      else PC1 = NULL;
    }

    (*PRECPC1).Suiv = NULL;             /* On a coupe P1 en deux polynomes de degre plus petit */

    while(PC2!=NULL && (*PC2).Deg > D){ /* meme operation avec P2 et PC2 */
      (*PC2).Deg -= (D+1);
      PRECPC2 = PC2;
      if((*PC2).Suiv != NULL){
	PC2 = (*PC2).Suiv;
      }
      else PC2 = NULL;
    }

    (*PRECPC2).Suiv = NULL;

    S = CopierPolynome(P1);             /* les quatre polynomes obtenus */
    T = CopierPolynome(PC1);            /* P1, PC1, P2 et PC2 */
    U = CopierPolynome(P2);             /* sont copies car ils seront detruits */
    V = CopierPolynome(PC2);            /* par addition */

    M = Multiplication(Addition(P1,PC1),Addition(P2,PC2)); /* M = (P1 + PC1)(P2 + PC2) Premiere multiplication */

    N = Multiplication(S,U);                               /* N = P1*P2 = S*U Deuxieme multiplication */

    O = Multiplication(T,V);                               /* O = PC1*PC2 = T*V Troisieme multiplication */

    Q = CopierPolynome(N);              /* N et O sont copies car ils seront detruits */
    R = CopierPolynome(O);              /* par soustraction */

    P = Soustraction(Soustraction(M,N),O);                 /* P = M - N - O */
    PC1 = Q;

    while(PC1 != NULL){                 /* PC1 parcours Q et remonte les degres */
      (*PC1).Deg += 2*D+2;              /* de 2*(D+1) */
      PC1 = (*PC1).Suiv;
    }
    PC1 = P;
    while(PC1 != NULL){                 /* PC1 parcours P et remonte les degres */ 
      (*PC1).Deg += D+1;                /* de D+1 */
      PC1 = (*PC1).Suiv;
    }

    return Addition(Addition(Q,P),R);   /* On retourne l'addition des trois polynomes */
  }
}

/*********************************************************/
/*                FONCTION MULTIPLICATION                */
/*                                                       */
/*********************************************************/

/* Multiplie deux polynomes quelconques en divisant le probleme */
/* en la somme de multiplications de polynomes de degres egaux  */
polynome* Multiplication(polynome *P1, polynome *P2){
  polynome *PC1, *PRECPC1, *PC2, *P, *PC3;
  int D, E;
  
  if (P1==NULL || P2==NULL) return NULL;   /* toute multiplication par un polynome nul, retourne un polynome nul */

  if( ((*P1).Suiv == NULL) || ((*P2).Suiv == NULL)){ 
    if( ((*P1).Suiv == NULL) && ((*P2).Suiv == NULL) ){ /* Multiplication d'un monome par un monome */
      (*P1).Deg += (*P2).Deg;                           /* On somme les degres */
      (*P1).Coeff *= (*P2).Coeff;                       /* On multiplie les coefficients */
      LibererPolynome(P2);                              /* On libere un des deux */
      return P1;
    }
    else if(((*P1).Suiv == NULL)){                      /* Multiplication d'un monome par un polynome */
      PC2 = P2;
      while(PC2 != NULL){                               /* On effectue les memes operations que plus haut */
	(*PC2).Deg += (*P1).Deg;                        /* sur l'ensemble des monomes du polynome */
	(*PC2).Coeff *= (*P1).Coeff;                    /* distinguer ce cas est un gain en complexite */
	PC2 = (*PC2).Suiv;                              /* car la complexite est fonction lineaire du degre */
      }
      return P2;
    }
    else{                                               /* On apelle le cas symetrique */
      return Multiplication(P2,P1);
    }
  }
  else{
    if( ((*P1).Deg) == ((*P2).Deg) ){                   /* Si les degres sont egaux on fait appel */
      return MultiplicationKaratsuba(P1,P2);            /* a MultiplicationKaratsuba */
    }
    else{
      if(((*P1).Deg <= 1) && ((*P2).Deg <= 1)){         /* Si les degres sont au plus de 1 on fait appel */
	return MultiplicationIntelligente(P1,P2);       /* a MultiplicationIntelligente  */
      }
      else if((*P1).Deg > (*P2).Deg){                   /* Si les degres sont differents celui de P1 > celui de P2 */
	D = (*P1).Deg;                                  /* D = degre de P1 */
	E = (*P2).Deg;                                  /* E = degre de P2 */
	PC1 = P1;
	PC3 = CopierPolynome(P2);                       /* On copie P2 dans PC3 car il sera detruit */
	while(PC1!=NULL && (*PC1).Deg >= D - E){                     /* On parcours une partie de P1 en baissant son degre */
	  (*PC1).Deg += E - D;                          /* de facon a faire apparaitre un polynome de meme degre que P2 */
	  PRECPC1 = PC1;
	  PC1 = (*PC1).Suiv;
	}
	(*PRECPC1).Suiv = NULL;
	P = Multiplication(P1,P2);                      /* P = produit des deux polynomes de meme degre */
	PC2 = P;
	while(PC2 != NULL){                             /* On retablit le bon degre de P car celui de P1 avait ete baisse */
	  (*PC2).Deg += D - E;
	  PC2 = (*PC2).Suiv;
	}
	
	return Addition(P,Multiplication(PC3,PC1));     /* On retourne alors P additionne au produit de P2 */
      }                                                 /* avec la partie manquante de P1 */
      else return Multiplication(P2,P1); 
    }
  }
}
