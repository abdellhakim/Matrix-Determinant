#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>


int n;
float ** alloc_Tab_2D(const int n);
float  manual_Tab_2D(float **T, int n);
float  aff_Tab_2D( float **T, int n);
float  det_Tab_2D(float **T, int n);
float  change_Tab_2d(float **T, int l,int c);
float  auto_Tab_2D(float **T, int n,int max,int min);
float  Aff_elem(float **T, int n);
float  Aff_elem_2(float **T, int n);
void permutation_Tab_2D(float **T,int l1,int l2,const int n);
int check_2D(float **T,const int n);
float** coef(float ** T,int n, int nC,int m);
float det_crammer_2d(float**T,int n);


int main()
{

    int w,l,c,T,q,max,min,ch;
    do
    {
        printf("\n\t*** Ce programme permet de calculer la matrice par methode de gauss et cramer  ***\n");
        printf("\n\t\tCree par Abdelhakim Ait Dabel\t 28/11/2022 \tVersion 2.0\n\n");
        getch();
        system("cls");
        float **M;
        int n,a;

        srand(time(NULL));

        do
        {
            printf("\n  Donner l'ordre de la matrice :  ");
            scanf("%d",&n);
        }
        while(n<0);


        printf("  \n  -- Voulez-vous ecrire la matrice manuellement ou automatiquement --\n ");
        do
        {
            printf("\n\t*Manuelle: 1\n\t*Automatique: 0\n");
            scanf("%d",&a);
        }
        while(a!=1&&a!=0) ;
        switch(a)
        {
        case 1:
            M=alloc_Tab_2D(n);
            manual_Tab_2D(M,n);
            aff_Tab_2D(M,n);
            break;
        case 0:
            printf("\n Donner l'intervalle des nombres  \n");
            printf(" Max = ");
            scanf("%d",&max);
            printf(" Min = ");
            scanf("%d",&min);
            M=alloc_Tab_2D(n);
            auto_Tab_2D(M,n,max,min);
            aff_Tab_2D(M,n);
            break;

        }

        printf("\n Voulez-vous changer l'une des valeurs de matrice  \n\t*Oui: 1\n\t*Non: 0  \n");
        scanf("%d",&w);
        if (w==1)
        {
            printf("\n Entrer la ligne : ");
            scanf("%d",&l);
            printf("\n Entrer la colonne :  ");
            scanf("%d",&c);
            change_Tab_2d(M,l,c);
            aff_Tab_2D(M,n);
            getch();
            system("cls");

        }
        printf("\n calculer la matrice par methode   \n\t*guass: 1\n\t*cramer: 0  \n");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            printf("Det =  %.3f\n",det_Tab_2D(M,n));
            break;
        case 0:
            printf("\nDet =  %.3f\n",det_crammer_2d(M,n));
            break;
        }
        //printf("Det =  %.3f\n",det_Tab_2D(M,n));
//printf("\nDet =  %.3f\n",det_crammer_2d(M,n));
        printf("\n Voulez-vous quitter le programme  \n\n\t*Oui: 1\n\t*Non: 0  \n");
        scanf("%d",&q);
        system("cls");

    }
    while(q==0 );
    return 0;

}

//allocation dynamique de la memoire
float ** alloc_Tab_2D(const int n)
{

    int i,**R;
    R  = (int ** )malloc(n*sizeof(int *));
    if(R==NULL)
    {
        printf("\n ERROR");
        exit(66);
    }
    for(i=0; i<n; i++)
    {
        R[i]=(int* )malloc(n*sizeof(int));
        if(R==NULL)
        {
            printf("\n ERROR");
            exit(66);
        }
    }

    return R;
}
float  manual_Tab_2D(float **T,int n)
{
    int i,j;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("\n Donnez T[%d][%d] : ",i,j);
            scanf("%f",&T[i][j]);
        }
    }

    return 0;
}
// remplissage auto de la matrice
float  auto_Tab_2D(float **T, int n, int max,int min)
{
    int i,j;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)

            T[i][j]= min + rand() % (max+1 - min);
    return 0;
}
// affichage de la matrice
float  aff_Tab_2D(float **T, int n)
{

    int i,j;
    for(i=0; i<n; i++)
    {
        printf("\n \t | ");

        for(j=0; j<n; j++)
            printf("%8.2f ",T[i][j]);

        printf(" | ");
        Sleep(100);

    }
    printf(" \n");
    Sleep(100);

    return 0;
}
//Changement d'une valeur de matrice
float  change_Tab_2d(float **T, int l,int c)
{

    printf("Entrer la nouvelle valeur de T[%d][%d] :",l,c);

    scanf("%f",&T[l][c]);
    return 0;
}
float  det_Tab_2D(float **T, int n)
{
    //convertion a la matrice triangulaire superieur

    float   pivot, det=1;
    int i,j,k,ans,occ=0;
    printf("    voulez-vous etapes par etapes : \n\t *Oui:1\n\t *Non:0\n");
    scanf("%d",&ans);
    for(i=0; i<n; i++)
    {
        occ+=check_2D(T,n);

        for(j=i+1; j< n; j++)
        {
            pivot = T[j][i]/T[i][i];

            for(k=0; k<n; k++)
            {

                T[j][k] = T[j][k] - pivot*T[i][k];

            }

            switch(ans)
            {
            case 1 :
                Aff_elem(T,n);
                break;
            case 0 :
                Aff_elem_2(T,n);
                break;
            }
        }

    }

    for(i=0; i< n; i++)
    {
        det*= T[i][i];
        for(j=0; j<occ; j++)
        {
            det*=-1;
        }
    }
    return det;
}
//affichage des etapes d elimination
float  Aff_elem(float **T, int n)
{
    int i,j;
    printf("\n");
    for(i=0; i<n; i++)
    {
        printf("\n \t       | ");

        for(j=0; j<n; j++)
            printf(" %8.2f ",T[i][j]);
        printf(" | ");

    }
    printf("\n\n");
    getch();

    printf(" \n\n ");

    return 0;
}
float  Aff_elem_2(float **T, int n)
{
    int i,j;
    printf("\n");
    for(i=0; i<n; i++)
    {
        printf("\n \t       | ");

        for(j=0; j<n; j++)
            printf(" %8.2f ",T[i][j]);
        printf(" | ");

    }
    printf("\n\n");

    printf(" \n\n ");

    return 0;
}
int check_2D(float **T,const int n)
{
    int i,j,occ=0,k;
    do
    {
        k=0;
        for (i=0 ; i<n; i++)
        {
            if((T[i][i]==0)&&(i!=n-1))
            {
                permutation_Tab_2D(T,i,i+1,n);
                printf("\nL%d <--> L%d\n",i,i+1);
                aff_Tab_2D(T,n);
                system("pause");
                occ++;
                k++;
            }
            if((T[i][i]==0)&&(i==n-1))
            {
                permutation_Tab_2D(T,i,0,n);
                printf("\nL%d <--> L%d\n",n,1);
                aff_Tab_2D(T,n);
                occ++;
                k++;
            }
        }
    }
    while(k!=0);
    return occ;
}
void permutation_Tab_2D(float **T,int l1,int l2,const int n)
{
    float z;
    int i;
    for(i=0; i<n; i++)
    {
        z=T[l1][i];
        T[l1][i]=T[l2][i];
        T[l2][i]=z;
    }
}
float det_crammer_2d(float**T,int n)
{int occ=0;
    float res=0;
    int i;
    float ** co;
    if(n >2)
    {
        for(i=0; i<n; i++)
        {
            occ+=check_2D(T,n);
            co=coef(T,n,0,i);
            res+=T[0][i]*((i%2==0)?1:-1)*det_crammer_2d(co,n-1);

        }
        for(i=0; i<n-1; i++)
            free(co[i]);
            free(co);
        return(res);
    }
    else if(n==2)
        return(T[0][0]*T[1][1]-T[0][1]*T[1][0]);
}

float** coef(float ** T,int n, int nb,int m)
{
    float **res;
    int i,j,k,l;
    res = alloc_Tab_2D(n);
    for(i=0,k=0; i<n-1&&k<n; i++,k++)
    {

        if(k==nb)k++;
        for(j=0,l=0;j<n-1&&l<n; j++,l++)
        {
            if(l==m)l++;
            res[i][j]=T[k][l];
        }
    }
    return res;
}
