
    #include <stdio.h>
    #include <stdlib.h>
    int main() {
      int *pointer;
      int i, n;
      printf( "Nombres d'elements a ajouter: " );
      scanf( "%d", &n ); /* Admettons que l'utilisateur insere 3 */
      pointer = ( int * ) calloc( n, sizeof( int ) );
      for( i = 0; i < n; i++ )
      {
        printf( "Entrez le numero N.%d", i );
        scanf( "%d", &pointer[i] ); /* Admettons que l'utilisateur insere 1 2 et 3 */
      }
      for( i = 0; i < n; i++ )
      {
        printf( "%d ", pointer[i] );
        /* Affiche 1 2 3 dans la console */
      }
      return 0;
    }
