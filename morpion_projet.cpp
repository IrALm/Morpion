/***********************************************************************************************************************
 PROJET  : JEU DE MORPION
 Fait par AGANZE LWABOSHI MOISE le 20 décembre 2023
 ***********************************************************************************************************************/


#include <iostream>   		// pour pouvoir utiliser cin, cout, endl
#include <fstream>   		// lecture/écriture de fichier
#include <ctime>            // pour le calcul du cout temporel de chaque fontion
using namespace std;

/*******************  Définition de la structure t_grille ****************************************************************/
/* Nous allons  utiliser un chainage simple terminé à null pour modéliser notre grille 
*/

typedef struct grille{
    char c ; // le symbole 
    int x,y; // les coordonnées
    grille *suivant; // un pointeur vers la case suivante

}grille;

typedef grille *t_grille; // notre t_grille est donc un pointeur vers la structure grille 

/*fonction vide 
  précondition : aucune
*/

t_grille vide(){
    return nullptr;
}
/* Post-condition : renvoir un t_grille vide */

/* Procédure detruire 
   Role : desalouer la mémoire allouée dynamiquement par la structure
   Pré : t_grille a bien été declarée dans le programme principal
*/

void detruire( t_grille p){

    t_grille nv ;
    while( p != nullptr){
        nv = p;
        p = p->suivant;
        delete nv;
    }
}

/* post-condition : libère la mémoire allouée par t_grille 
*/

/* Procédure permettant de faire une  saisie controlée 
   dans le cas où le joueur essaie de jouer dans une case déjà occupée
   Précondition : Aucune 
*/
void saisie( int &x , int &y , t_grille ptr){
    while( ptr != nullptr){
        if( ptr->x == x && ptr->y == y ){
            cout << endl << " °°°° Désolé , l'un des deux joueurs a déjà utilisé cette case °°°° " << endl 
                 << " saisir x  puis espace suivi de y : ";
            cin >> x >> y ;
        }
        ptr = ptr->suivant;
    }
}
/* Post-condition : effectue la saisie controlée dans le cas où la case est occupée */

/* procédure placer permettant de placer le symbole sur la grille 
   précondition : tous les paramètres doivent etre bien declarés
*/

void placer( char c , int &x , int &y , t_grille &ptr ){

    if( ptr == nullptr ){
        ptr = new grille ;
        ptr->c = c ;
        ptr->x = x ;
        ptr->y = y ;
        ptr->suivant = nullptr ;
    }

    // ajout en tete

    else{
        saisie( x , y , ptr); // on effectue la saisie controlée si la case des coordonnées x,y est occupée
        t_grille tmp ;
        tmp = new grille ;
        tmp->c = c ;
        tmp->x = x ;
        tmp->y = y ;
        tmp->suivant = ptr ;
        ptr = tmp ;
    }
    
}
/* Post-condition : modifie le chainage en placant le symbole dans la grille 
   cout : étant un ajout en tete du chainage , le cout est donc constant
*/

/* algorithme de recherche 
    fonction me permettant de savoir les coordonées sont
    dans la grille et si le symbole se trouve exactement dans la case représentée par ces coordonnées
    Pre : Aucune à part que les paramètres doivent etre bien declarés dans le programme principal
*/

bool chercher(char c, int x, int y, t_grille ptr) {
    while (ptr != nullptr) {
        if (ptr->x == x && ptr->y == y && ptr->c == c) {
            return true;
        }
        ptr = ptr->suivant;
    }
    return false;
}
/* post : renvoie vrai si c'est le cas , faux si c'est le contraire*/

/* fonction pour verifier la victoire sur la ligne
   petite explication du fonctionnement :
   de la case donnée F des coordonées (x,y) , on verifie si les cases à gauche et à droite de F 
   contiennent le meme symbole que F , si ces cases à gauche et à droite sont au nombre de 4 ,
   ajouté avec la case de F , ca fait 5 symbole successif et donc : Victoire!
   Bien sur la fonction marche sans regarder le contenu de la case F
   on verifier à droite à partir de x+1 et à gauche à partir de x-1 , y ne bouge pas car c'est le principe pour une victoire sur la ligne 
*/

bool verif_lg( char c , int x , int y , t_grille ptr ){
    int i ;
    int nb = 0 ;
    bool b ;
    i = x + 1 ;
    while(nb < 4 ){
        b = chercher( c ,i , y , ptr);
        if(b){
            i++; 
            nb += 1 ;
        }
        else{ break ; }
    }
    if( nb != 4){

        i = x - 1;
        while(nb < 4 ){
            b = chercher( c , i , y , ptr);
            if(b){
                i--; 
                nb += 1 ;
            }
            else{ break ; }
        }
    }
    if( nb == 4 ){ return true ;}
    else{ return false; }
}
/* Post- condition : renvoie vrai si victoire , faus sinon */

/* fonction vérifier victoire colonne 
   meme principe que la fonction précedente
   meme préconditions et meme post-condition
*/
bool verif_col( char c , int x , int y , t_grille ptr ){
    int i ;
    int nb = 0 ;
    bool b ;
    i = y + 1 ;
    while(nb < 4 ){
        b = chercher( c ,x , i , ptr);
        if(b){
            i++; 
            nb += 1 ;
        }
        else{ break ; }
    }
    if( nb != 4 ){
        i = y - 1;
        while( nb < 4 ){
            b = chercher( c , x , i , ptr);
            if(b){
                i--; 
                nb += 1 ;
            }
            else{ break ; }
        }
    }
    if( nb == 4 ){ return true ;}
    else{ return false; }
}

/* fonction vérifier victoire sur la diagonale
   meme principe que la fonction précedente
   meme préconditions et meme post-condition
   Juste un peu complexe car il y a 4 cas à distinguer
   comparer aux autres qui n'ont que 2 
*/

bool verif_diag( char c , int x , int y , t_grille ptr ){
    int i , j ;
    bool b ;
    int nb = 0 ;
    //cas 1 

    i = x + 1 ;
    j = y + 1 ;

    while(nb < 4 ){
        b = chercher( c ,i , j , ptr);
        if(b){
            i++; 
            j++;
            nb += 1 ;
        }
        else{ break ; }
    }

    // cas 2 
    if( nb != 4 ){
        i = x + 1 ;
        j = y - 1 ;
        while( nb < 4 ){
            b = chercher( c ,i , j , ptr);
            if(b){
                i++; 
                j--;
                nb += 1 ;
            }
            else{ break ; }
        }
    }
    // cas 3 
    if( nb != 4 ){
        i = x - 1 ;
        j = y + 1 ;
        while(nb < 4 ){
            b = chercher( c ,i , j , ptr);
            if(b){
                i--; 
                j++;
                nb += 1 ;
            }
            else{ break ; }
        }
    }
    // cas 4
    if( nb != 4 ){
        i = x - 1 ;
        j = y - 1 ;
        while(nb < 4 ){
            b = chercher( c ,i , j , ptr);
            if(b){
                i--; 
                j--;
                nb += 1 ;
            }
            else{ break ; }
        }
    }
    if( nb == 4 ){ return true ;}
    else{ return false; }
}

/* fonction gagnant
   verifier le joeur qui a gagné
   et fait appel aux 3 méthodes de verification de la victoire 
   en fonction des cas.
   renvoie vrai si Victoire , faux sinon
   cout : dans le pire de cas , on parcourera tout le chainge ( 1 ou 2 , voir 3 fois peut-etre)
          donc on peut dire qu'il peut etre linéaire ( ou quadratique : cela depend des cas )
*/
bool gagnant(char c , int x , int y , t_grille ptr){

    bool verif;
    verif = verif_lg( c , x , y , ptr );
    if(verif){ return true ;}
    else{
        verif = verif_col( c , x , y , ptr );
        if(verif){ return true ;}
        else{
            verif = verif_diag( c , x , y , ptr );
            if( verif){ return true ;}
            else{ return false ;}
        }
    }
}
/* ****************** concerne l'affichage de la grille ****************************************************************/

// fonction me permettant de trouver le plus garnd x dans le chainage
// post-condion : renvoie le plus grand x
// précondition : il y a au moins un élément dans t_grille

int max_x( t_grille ptr){
    int max = ptr->x ;
    while( ptr->suivant != nullptr ){
        if( ptr->suivant->x > max){
            max = ptr->suivant->x ;
        }
        ptr = ptr->suivant;
    }
    return max ;
}

// fonction me permettant de trouver le plus petit x dans le chainage
// post-condion : renvoie le plus petit x
// précondition : il y a au moins un élément dans t_grille

int min_x( t_grille ptr){
    int min = ptr->x ;
    while( ptr->suivant != nullptr ){
        if( ptr->suivant->x < min){
            min = ptr->suivant->x ;
        }
        ptr = ptr->suivant;
    }
    return min ;
}
// fonction me permettant de trouver le plus garnd y dans le chainage
// post-condion : renvoie le plus grand y
// précondition : il y a au moins un élément dans t_grille

int max_y( t_grille ptr){
    int max = ptr->y  ;
    while( ptr->suivant != nullptr ){
        if( ptr->suivant->y > max){
            max = ptr->suivant->y ;
        }
        ptr = ptr->suivant;
    }
    return max ;
}

// fonction me permettant de trouver le plus petit y dans le chainage
// post-condion : renvoie le plus petit y
// précondition : il y a au moins un élément dans t_grille

int min_y( t_grille ptr){
    int min = ptr->y ;
    while( ptr->suivant != nullptr ){
        if( ptr->suivant->y < min){
            min = ptr->suivant->y ;
        }
        ptr = ptr->suivant;
    }
    return min ;
}
/* fonction me permettant d'afficher le bon symbole 
   verifie si (x,y) se trouve dans le chainage et affiche le contenu
*/
bool est_dans(int i, int j, t_grille ptr) {
    while (ptr != nullptr) {
        if (ptr->x == i && ptr->y == j) {
            cout << "  " << ptr->c;
            return true;
        }
        ptr = ptr->suivant;
    }
    return false;
}
/* procédure d'affichage de la grille 
   affiche les lignes verticalement
   et les colonnes horizontalement
   affiche de la plus grande valeaur à la plus petite valeur
   Ainsi donc , pour une victoire en ligne , la succession de 5 symboles sera affichée verticalemnt
   pour une victoire en colonne : la succession de 5 symboles sera affiché horieontalement
*/
void affiche_grille(t_grille ptr) {
    
        for (int i = max_x(ptr); i >= min_x(ptr); i--) {
            cout << endl;
            for (int j = max_y(ptr); j >= min_y(ptr); j--) {
                if (est_dans(i, j, ptr)) {} 
                else {
                    cout << "  " << '-';
                }
            }
        }
        cout << endl;
}

/*  Enregister la partie dans un fichier 
    cette procédure enregistre l'affichage dans un fichier texte
    le principe est le meme que pour la procédure affiche_grille
*/
void ecrire_fichier_manche( string nom_fichier , t_grille ptr){
    fstream flux ;
    t_grille nv;
    bool b ;
    flux.open(nom_fichier, ios::out);
    if (flux.is_open()) {
        for (int i = max_x(ptr); i >= min_x(ptr); i--) {
            flux << endl;
            for (int j = max_y(ptr); j >= min_y(ptr); j--) {
                nv = ptr ;
                b = false ;
                while (nv != nullptr) {
                    if (nv->x == i && nv->y == j) {
                        flux << "  " << nv->c;
                        b = true ;
                    }
                    nv = nv->suivant;
                }
                if(!b){
                flux << "  " << '-';}
            }
        }
        flux << endl;
        flux.close();
        cout << endl << endl << " °°°°° Un fichier " << nom_fichier << " a été crée contenant le resultat de cette manche comme preuve de fonctionnement °°°°° " << endl ;

    }
    else {
       cout << "Erreur : impossible de générer le fichier " << nom_fichier << endl;
   }
   detruire(nv);
}

/*********************************************************  PROGRAMME PRINCIPAL  *********************************************************************************************************/

int main(){

    t_grille ptr ;
    char jr , plr ;
    int x , y ;
    bool winner ;
    clock_t debut ;
    clock_t fin ; 
    double temps_ecoulee ; 

    cout << endl << " ******************* JEU DE MORPION *************************  " << endl ;
    cout << endl << " Saisir le symbole du Premier joueur : ";
    cin >> jr ;
    cout << endl << " Saisir le symbole du Deuxième joueur : ";
    cin >> plr ;
    cout << endl << endl << " ************* DEBUT DU JEU ************************ " << endl ;
    int i = 1 ;
    while( i <= 3 ){

        debut = clock(); // j'enregistre temps de debut

        ptr = vide() ; // appel de la fonction 

        fin = clock() ; // j'enregistre le temps de fin 

        temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
        cout << endl << endl << " temps ecoulé pour la fonction vide : " << temps_ecoulee << " secondes " << endl << endl ; // affichage

        if( i == 1 ){
            cout << endl << endl << " ********** " << i << " ère Manche ********** " ;
        }
        else{
            cout << endl << endl << " ********** " << i << " ème Manche ********** " ;
        }
        while(true){
            cout << endl << " ***** Premier joueur : ***** "
                << endl << " Saisir la valeur de x suivi d' un espace puis de la valeur de y : " ;
            cin >> x  >> y ;

            debut = clock(); // j'enregistre temps de debut
            placer(jr , x , y , ptr); // appel de la procédure
            fin = clock() ; // j'enregistre le temps de fin 

            temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
            cout << endl << endl << " temps ecoulé pour la procedure placer : " << temps_ecoulee << " secondes " << endl << endl ; // affichage
            
            debut = clock(); // j'enregistre temps de debut
            winner = gagnant(jr , x,  y,ptr); // appel de la fonction gagnant
            fin = clock() ; // j'enregistre le temps de fin 

            temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
            cout << endl << endl << " temps ecoulé pour la fonction gagnant : " << temps_ecoulee << " secondes " << endl << endl ; // affichage
            if( winner ){
                cout << endl << " ********** Le Premier joueur a remporté la partie ! ********** " ;
                break;
            }
            cout << endl << " ***** Deuxième joueur : ***** "
                << endl << " Saisir la valeur de x suivi d' un espace puis de la valeur de y : " ;
            cin >> x  >> y ;

            debut = clock(); // j'enregistre temps de debut
            placer(plr , x , y , ptr);// appel de la fonction 
            fin = clock() ; // j'enregistre le temps de fin 

            temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
            cout << endl << endl << " temps ecoulé pour la procedure placer : " << temps_ecoulee << " secondes " << endl << endl ; // affichage

            debut = clock(); // j'enregistre temps de debut
            winner = gagnant(plr , x,  y,ptr); // appel de la fonction gagnant
            fin = clock() ; // j'enregistre le temps de fin

            temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
            cout << endl << endl << " temps ecoulé pour la fonction gagnant : " << temps_ecoulee << " secondes " << endl << endl ; // affichage

            if( winner ){
                cout << endl << " ********** Le Deuxième joueur a remporté la partie ! ********** " ;
                break;
            }
        }
        debut = clock(); // j'enregistre temps de debut
        affiche_grille( ptr );
        fin = clock() ; // j'enregistre le temps de fin

        temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
        cout << endl << endl << " temps ecoulé pour la procédure d'affichage : " << temps_ecoulee << " secondes " << endl << endl ; // affichage

        if( i == 1 ){
            debut = clock(); // j'enregistre temps de debut
            ecrire_fichier_manche("Manche_1.txt", ptr); // appel de la procédure d'ecriture
            fin = clock() ; // j'enregistre le temps de fin
            temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
            cout << endl << endl << " temps ecoulé pour la procédure d'écriture dans le fichier: " << temps_ecoulee << "  secondes " << endl << endl ; // affichage
        }
        if( i == 2 ){

            debut = clock(); // j'enregistre temps de debut
            ecrire_fichier_manche("Manche_2.txt", ptr); // appel de la procédure d'ecriture
            fin = clock() ; // j'enregistre le temps de fin
            temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
            cout << endl << endl << " temps ecoulé pour la procédure d'écriture dans le fichier: " << temps_ecoulee << " secondes " << endl << endl ; // affichage
        }
        if( i == 3 ){

            debut = clock(); // j'enregistre temps de debut
            ecrire_fichier_manche("Manche_3.txt", ptr); // appel de la procédure d'ecriture
            fin = clock() ; // j'enregistre le temps de fin
            temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
            cout << endl << endl << " temps ecoulé pour la procédure d'écriture dans le fichier: " << temps_ecoulee << " secondes " << endl << endl ; // affichage
        }
        debut = clock(); // j'enregistre temps de debut
        detruire(ptr); // appel de la procédure detruire
        fin = clock() ; // j'enregistre le temps de fin

        temps_ecoulee = static_cast<double>(fin - debut)/CLOCKS_PER_SEC; // je calcul le temps ecoulée
        cout << endl << endl << " temps ecoulé pour la procédure détruire : " << temps_ecoulee << " secondes " << endl << endl ; // affichage
        i ++ ;
    }
    cout << endl << endl << " ***************************************************** FIN ********************************************** " << endl  ; 
}
