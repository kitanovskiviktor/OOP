Да се дефинира структура RabotnaNedela во која се чуваат бројот на работни часови за секој работен ден во неделата (5 дена) и број на неделата. Потоа да се дефинира структура Rabotnik за кој се чува име (низа од 50 знаци) и низа од работни недели (макс 4).

Да се имплементираат следните функции:

int maxNedela(Rabotnik *r) која за проследениот работник ќе го врати бројот на неделата со најмногу работни часови
void table(Rabotnik *r, int n) која за низата од работници ќе отпечати приказ во следниот формат:
Пример

Rab     1   2   3   4   Vkupno
Brianna 192 238 226 225 881
Ava     236 231 184 212 863
Matthew 236 235 219 243 933
Alyssa  240 254 217 228 939
Emma    247 205 204 242 898 
каде во секој ред се печати името на работникот и вкупниот број на работни часови за секоја работна недела, како и вкупниот број на часови за сите недели. Во рамките на редот податоците се разделени со знак за табулатор \t.

#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

struct RabotnaNedela
{
    int casovi[DENOVI];
    int nedela;
};
 
typedef struct RabotnaNedela RN;
 
// ovde strukturata Rabotnik
 
struct Rabotnik
{
    char ime[50];
    RN nedeli[NEDELI];
};
 
typedef struct Rabotnik R;
 
// ovde funkciite
 
int maxNedela(R *r)
{
    int i,j,tmp,vkupno=0,max=0;
 
    for(i=0;i<5;i++)
    {
        max+=r->nedeli[0].casovi[i];
        tmp=1;
    }
 
    for(i=1;i<4;i++)
    {
        vkupno=0;
        for(j=0;j<5;j++)
        {
            vkupno+=r->nedeli[i].casovi[j];
        }
        if(vkupno>max)
        {
            max = vkupno;
            tmp=i+1;
        }
    }
    return tmp;
}
 
void table(R *r, int n)
{
    int i,j,k,vkupno,vkupno2;
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(i=0; i<n; i++)
    {
        vkupno2=0;
        printf("%s\t",r[i].ime);
        for(j=0;j<4;j++)
        {
            vkupno=0;
            for(k=0;k<5;k++)
            {
                vkupno+=r[i].nedeli[j].casovi[k];
            }
            vkupno2+=vkupno;
            printf("%d\t",vkupno);
        }
        printf("%d\n",vkupno2);
    }
}
 
int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }
 
        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}