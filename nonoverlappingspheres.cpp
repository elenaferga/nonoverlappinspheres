//Programa que lee los centros de las esferas y de los puntos usados en la triangulación, calcula los radios de las esferas como las distancias más 
//cercanas a los puntos usados en la triangulación y elimina las esferas que se superponen quedándose con las de mayor radio.
using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
//Numero de elementos de datos.txt
const int NUM1 = 10;
//Numero de elementos de centros.txt
const int NUM = 23;
vector<double> xcentro, ycentro, zcentro, x, y, z, r, d;
vector<double> rad, xf, yf, zf;
double a,b,c;

int main()
{
    ifstream leer1, leer2;
    ofstream escribir;
    int i, j, k;

//------------------------------------------------------------------------------------------------------------------------------------
    // abrir los ficheros que contienen las coordenadas de los centros de las esferas y los puntos que he usado para la triangulación
    leer1.open("centros.txt");
    leer2.open("datos.txt");
        while (!leer1.eof())
        {
                leer1 >> a;
                leer1 >> b;
                leer1 >> c;

                xcentro.push_back(a);
                ycentro.push_back(b);
                zcentro.push_back(c);
            
        }
        while (!leer2.eof())
        {
                leer2 >> a;
                leer2 >> b;
                leer2 >> c;

                x.push_back(a);
                y.push_back(b);
                z.push_back(c);
            
        }
        // cerrar los ficheros
        leer1.close();
        leer2.close();
//------------------------------------------------------------------------------------------------------------------------------------

        //Muestro por pantalla los seis vectores para asegurarme de que se han copiado bien
        cout << "Centros" << endl;
        for (i = 0; i != xcentro.size(); i++)
        {

            cout << i << "."
                 << " xcentro: " << xcentro[i] << " ycentro: " << ycentro[i] << " zcentro: " << zcentro[i] << endl;
    }
    cout << "----------------------------------" << endl;
    cout << "Puntos iniciales" << endl;

    for (i = 0; i != x.size(); i++)
    {

        cout << i << "."
             << " x: " << x[i] << " y: " << y[i] << " z: " << z[i]  << endl;
    }
    cout << "----------------------------------" << endl;

//------------------------------------------------------------------------------------------------------------------------------------

    // Calculo las distancias desde el centro de una esfera hasta cada uno de los puntos de la triangulación. La distancia más pequeña define el radio de 
    //la esfera
    for (i = 0; i != xcentro.size(); i++)
        {
            //insertamos el valor 2 en la tercera posición del array
            r.insert(r.begin()+i, 10000);
            for (j = 0; j != xcentro.size(); j++)
                {
                    d.insert(d.begin() + i, sqrt(pow(xcentro[i] - x[j], 2) + pow(ycentro[i] - y[j], 2) + pow(zcentro[i] - z[j], 2)));
                    if (d[i] <= r[i])
                    {
                        r[i] = d[i];
                    }
                }
        }
    //Muestro por pantalla las coordenadas de la esfera y su radio
    for(i=0; i!=NUM; i++)
    {
        cout << "Centro ->" << "  x:" << xcentro[i] << "  y:" << ycentro[i] << "  z:" << zcentro[i] << "   Radio   -> " << r[i] << endl;
    }    
//------------------------------------------------------------------------------------------------------------------------------------

//Primero voy a ordenar R y reordenador xcentro, ycentro y zcentro de la misma manera dejando en primera posicion la esfera mas grande
double aux_elem, aux_elem1, aux_elem2, aux_elem3;
for(i=0; i!=NUM; i++)
    {
        for(j=0; j!=NUM-1; j++)
        {
            if(r[j]<r[j+1])
            {
                aux_elem = r[j];
                aux_elem1 = xcentro[j];
                aux_elem2 = ycentro[j];
                aux_elem3 = zcentro[j];
                r[j] = r[j+1];
                xcentro[j] = xcentro[j+1];
                ycentro[j] = ycentro[j+1];
                zcentro[j] = zcentro[j+1];
                r[j+1] = aux_elem;
                xcentro[j+1] = aux_elem1;
                ycentro[j+1] = aux_elem2;
                zcentro[j+1] = aux_elem3;
            }
        }
    }
    cout << "Esferas ya ordenadas" << endl;
    for (i = 0; i != NUM; i++)
    {
       
        cout << "Centro ->"
             << "  x:" << xcentro[i] << "  y:" << ycentro[i] << "  z:" << zcentro[i] << "   Radio   -> " << r[i] << endl;
    }

    //Me queda ver cuáles se superponen y eliminar las más pequeñas. Voy a ver para cada esfera hay otra que esté parcial o completamente dentro de la 
    // primera y me quedo con la más grande. La más pequeña la elimino directamente para no volver a tenerla en cuenta después.

    i=0;
    for (vector<double>::iterator h = xcentro.begin(); h != xcentro.end(); h++)
    {
        j=0;
        for (vector<double>::iterator w = xcentro.begin(); w != xcentro.end(); w++)
        {
            d.insert(d.begin() + i, sqrt(pow(xcentro[i] - xcentro[j], 2) + pow(ycentro[i] - ycentro[j], 2) + pow(zcentro[i] - zcentro[j], 2)));
            cout << "i: " << i << endl;
            cout << "j: " << j << endl;
            cout << "Radio i : " << r[i] << "Radio j: " << r[j] << endl;

            if ((d[i] < (r[i] + r[j])) && (r[i] >= r[j]) && (i != j))
            {
                //eliminar la esfera j-esima
                r.erase(r.begin() + j);
                xcentro.erase(xcentro.begin() + j);
                ycentro.erase(ycentro.begin() + j);
                zcentro.erase(zcentro.begin() + j);
                cout << "Dora1" << endl;
                w--;
            }
            if ((d[i] < (r[i] + r[j])) && (r[i] < r[j]))
            {
                //eliminar la esfera i-esima
                r.erase(r.begin() + i);
                xcentro.erase(xcentro.begin() + i);
                ycentro.erase(ycentro.begin() + i);
                zcentro.erase(zcentro.begin() + i);
                cout << "Dora2" << endl;
                w--;
            }
            if (d[i] >= (r[i] + r[j]))
            {
                //eliminar la esfera j-esima
                r.erase(r.begin() + j);
                xcentro.erase(xcentro.begin() + j);
                ycentro.erase(ycentro.begin() + j);
                zcentro.erase(zcentro.begin() + j);
                cout << "Dora3" << endl;
                w--;
            }

            j++;
        }
    i++;    
}
//Escribo los centros y radios de las esferas non-overlapping en el fichero de salida. 
escribir.open("nonoverlapping.txt");

for(i=0; i!=NUM; i++)
    {
        escribir << i << "."
                 << " x: " << xcentro[i] << " y: " << ycentro[i] << " z: " << zcentro[i] << " Radio: " << r[i] << endl;
    }
escribir.close();

    return 0;
}