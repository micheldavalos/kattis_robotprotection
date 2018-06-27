#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

#define XX first
#define YY second
#define Punto pair<double, double>

Punto p0;

struct compare1 {
    bool operator()(const Punto &p1, const Punto &p2)
    {
        if (p1.XX == p2.XX) {
            return p1.YY > p2.YY;
        }
        return p1.XX > p2.XX;
    }
};

double polarAngle(const Punto &p1, const Punto &p2)
{
    return atan2(p2.YY - p1.YY, p2.XX - p1.XX);
}

struct compare2 {
    bool operator()(const Punto &p1, const Punto &p2)
    {
        //cout <<  polarAngle(p0, p1) << " " <<  polarAngle(p0, p2) << endl;
        return polarAngle(p0, p1) > polarAngle(p0, p2);
    }
};

double direction(const Punto &a, const Punto &b, const Punto &c)
{
    return (b.XX - a.XX) * (c.YY - a.YY) - (c.XX - a.XX) * (b.YY - a.YY);
}


double area(const vector<Punto> &s)
{
    double suma = 0;
    int i;
    for (i = 0; i < s.size() - 1; ++i) {
        suma += s[i].XX * s[i+1].YY -
                s[i].YY * s[i+1].XX;
    }

    suma += s[i].XX * s[0].YY -
            s[i].YY * s[0].XX;

    return abs(suma/2);

}

int main()
{

    int n;
    Punto p;
    double x, y;

    cout << fixed << setprecision(1) << endl;
    while (cin >> n, n != 0) {
        priority_queue<Punto, vector<Punto>, compare1> pq;
        priority_queue<Punto, vector<Punto>, compare2> puntos;

        for (int i = 0; i < n; ++i) {
            cin >> p.XX >> p.YY;
            pq.push(p);
        }

        p0 = pq.top();
        pq.pop();

        while (!pq.empty()) {
            puntos.push(pq.top());
            pq.pop();
        }

        /*while (!puntos.empty()) {
      p = puntos.top();
      cout << p.XX << ", " << p.YY << endl;
      puntos.pop();
      }*/
        vector<Punto> pila;
        if (puntos.size() >= 2) {
            pila.push_back(p0);
            pila.push_back(puntos.top());
            puntos.pop();
            pila.push_back(puntos.top());
            puntos.pop();
            while (!puntos.empty()) {
                p = puntos.top();
                puntos.pop();
                //size_t s = pila.size();
                while ( direction(pila[pila.size()-2], pila[pila.size()-1], p) <= 0 ) {
                    pila.pop_back();
                    if (pila.size() < 3) {
                        break;
                    }
                }
                pila.push_back(p);
            }

            /*for (size_t i = 0; i < pila.size(); ++i) {
          cout << pila[i].XX << " " << pila[i].YY << endl;
        }*/

            cout << area(pila) << endl;
        } else {
            cout << "0.0" << endl;
        }


    }


    return 0;
}
