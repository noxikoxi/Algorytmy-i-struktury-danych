#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <cmath>

// Postac kwaternionu: a + bi + cj + dk
template <typename T>
class Quaternion{
    private:
        T a;
        T i;
        T j;
        T k;

    public:
        Quaternion() : a(T()), i(T()), j(T()), k(T()){} // Domyślny konstruktor
        ~Quaternion(){}; // Destruktor 

        // Konstruktor z parametrami
        Quaternion(T realVal, T iVal, T jVal, T kVal) : a(realVal), i(iVal), j(jVal), k(kVal){}

        // Konstruktor kopiujący
        Quaternion(const Quaternion &q)
        {
            a = q.a;
            i = q.i;
            j = q.j;
            k = q.k;
        }

        // Konstruktor przenoszący
        Quaternion(Quaternion &&q)
        {
            if(this != &q)
            { 
                a = std::move(q.a);
                i = std::move(q.i);
                j = std::move(q.j);
                k = std::move(q.k);

                q.a = q.i = q.j = q.k = T();
            }
        }
        
        // Przypisanie kopiujące
        Quaternion& operator=(const Quaternion &q)
        {
            a = q.a;
            i = q.i;
            j = q.j;
            k = q.k;

            return *this;
        }

        // Przypisanie przenoszące
        Quaternion& operator=(Quaternion &&q)
        {
            if(this != &q)
            {
                a = std::move(q.a);
                i = std::move(q.i);
                j = std::move(q.j);
                k = std::move(q.k);

                q.a = q.i = q.j = q.k = T();
            }

            return *this;
        }

        T real() const{return a;}; // Zwraca rzeczywista część kwaternionu
        T getI() const{return i;}; // Zwraca urojoną część kwaternionu przy i
        T getJ() const{return j;}; // Zwraca urojoną część kwaternionu przy j
        T getK() const{return k;}; // Zwraca urojoną część kwaternionu przy k


        Quaternion operator+ (const Quaternion &q) const;
        Quaternion operator- (const Quaternion &q) const;
        Quaternion operator* (const Quaternion &q) const;

        // Mnożenie przez skalar
        Quaternion operator* (T val) const;

        bool operator== (const Quaternion &q) const;
        bool operator!= (const Quaternion &q) const;

        // Sprzężenie kwaternionu
        Quaternion conjugate() const
        {
            return Quaternion(a, -i, -j, -k);
        }

        // Norma kwaternionu (Moduł)
        T norm() const
        {
            return std::sqrt(a*a + i*i + j*j + k*k);
        }

        // Wyświetla kwaternion jako sume algebraiczną
        void display();
};

// Pomocnik do wyświetlania
template<typename T>
std::string getSign(T val)
{
    if(val >= 0) return " + ";
    else return " - ";
}

// Pomocnik do wyświetlania
template<typename T>
void nicePrint(T val, std::string valName)
{
    if(val == 0) std::cout <<"";
    else if(std::abs(val) == 1) std::cout << getSign(val) << valName;
    else std::cout << getSign(val) << std::abs(val) << valName;
}

template<typename T>
void Quaternion<T>::display()
{
    std::cout << a;
    nicePrint(i, "i");
    nicePrint(j, "j");
    nicePrint(k, "k");
    std::cout << "\n";
}

template<typename T>
Quaternion<T> Quaternion<T>::operator+ (const Quaternion<T> &q) const
{
    return Quaternion<T>(a + q.a, i + q.i, j + q.j, k + q.k);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator- (const Quaternion<T> &q) const
{
    return Quaternion<T>(a - q.a, i - q.i, j - q.j, k - q.k);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator* (const Quaternion<T> &q) const
{
    T newA = a * q.a - i * q.i - j * q.j - k * q.k;
    T newI = a * q.i + i * q.a + j * q.k - k * q.j;
    T newJ = a * q.j - i * q.k + j * q.a + k * q.i;
    T newK = a * q.k + i * q.j - j * q.i + k * q.a;

    return Quaternion<T>(newA, newI, newJ, newK);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator* (T val) const
{
    return Quaternion<T>(a * val, i * val, j * val, k *val);
}

template<typename T>
bool Quaternion<T>::operator== (const Quaternion<T> &q) const
{
    if(a == q.a && i == q.i && j == q.j && k == q.k) return true;
    else return false;
}

template<typename T>
bool Quaternion<T>::operator!= (const Quaternion<T> &q) const
{
    return !(*this == q);
}
#endif