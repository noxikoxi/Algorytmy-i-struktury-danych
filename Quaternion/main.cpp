#include "quaternion.h"
#include "cassert"

// Sprawdza konstrukotry i przy okazji wyświetlanie
void testConstructors();

// Sprawdza najprostsze metody
void testSimpleMethods();

// Sprawdza operatory
void testOperators();

int main()
{
    testConstructors();
    testSimpleMethods();
    testOperators();

}

// Sprawdza, czy kwaternion ma prawidlowe wartosci
template<typename T>
void assertQuaternionVals(const Quaternion<T> &q, T rVal, T iVal, T jVal, T kVal)
{
    assert(q.real() == rVal);
    assert(q.getI() == iVal);
    assert(q.getJ() == jVal);
    assert(q.getK() == kVal);
}

void testConstructors()
{
    std::cout << "*** TEST KONSTRUKTOROW ***\n";
    Quaternion<double> q1;
    Quaternion<double> q2(-1, -1, -1, -1);
    Quaternion<double> q3(5, 0, 0, -2);
    Quaternion<double> q4(2, 9, -3, 0);
    Quaternion<double> q5(-3, -5, 0, -2);
    Quaternion<double> q6(q5);
    
    assertQuaternionVals(q1, 0.0, 0.0, 0.0, 0.0);
    assertQuaternionVals(q2, -1.0, -1.0, -1.0, -1.0);
    assertQuaternionVals(q3, 5.0, 0.0, 0.0, -2.0);
    assertQuaternionVals(q4, 2.0, 9.0, -3.0, 0.0);
    assertQuaternionVals(q5, -3.0, -5.0, 0.0, -2.0);
    assertQuaternionVals(q6, -3.0, -5.0, 0.0, -2.0);
    
    std::cout << "q1: ";
    q1.display();
    std::cout << "q2: ";
    q2.display();
    std::cout << "q3: ";
    q3.display();
    std::cout << "q4: ";
    q4.display();
    std::cout << "q5: ";
    q5.display();
    std::cout << "q6: ";
    q6.display();
    std::cout << "Po q7 = std::move(q2)\n";

    Quaternion<double> q7(std::move(q2));
    std::cout << "q2: ";
    q2.display();
    std::cout << "q7: ";
    q7.display();

    assertQuaternionVals(q2, 0.0, 0.0, 0.0, 0.0);
    assertQuaternionVals(q7, -1.0, -1.0, -1.0, -1.0);
}

void testSimpleMethods()
{
    std::cout << "\n*** TEST PROSTYCH METOD ***\n";
    Quaternion<double> q(1.2, 2.3, 3.4, 4.5);

    std::cout << "q: ";
    q.display();

    std::cout << "Rzeczywista czesc q: " << q.real() << "\n";
    std::cout << "Wartosc urojonego i w q: " << q.getI() << "\n";
    std::cout << "Wartosc urojonego j w q: " << q.getJ() << "\n";
    std::cout << "Wartosc urojonego k w q: " << q.getK() << "\n";

    assertQuaternionVals(q, 1.2, 2.3, 3.4, 4.5);

    std::cout << "Sprzężenia q: ";
    q.conjugate().display();

    assertQuaternionVals(q.conjugate(), q.real(), -q.getI(), -q.getJ(), -q.getK());

    std::cout << "Moduł q: " << q.norm() << "\n";

    assert(q.norm() == sqrt(38.54));
}

void testOperators()
{
    std::cout << "\n*** TEST OPERATORÓW ***\n";
    Quaternion<int> q1(2, 3, 4, 5);
    Quaternion<int> q2(5, -2, 4, 5);

    assertQuaternionVals(q1, 2, 3, 4, 5);
    assertQuaternionVals(q2, 5, -2, 4, 5);

    std::cout << "q1: ";
    q1.display();
    std::cout << "q2: ";
    q2.display();

    std::cout << "(q1 + q2):  ";
    (q1 + q2).display();

    assertQuaternionVals(q1 + q2, q1.real() + q2.real(), q1.getI() + q2.getI(), q1.getJ() + q2.getJ(), q1.getK() + q2.getK());

    std::cout << "(q1 - q2):  ";
    (q1 - q2).display();

    assertQuaternionVals(q1 - q2, q1.real() - q2.real(), q1.getI() - q2.getI(), q1.getJ() - q2.getJ(), q1.getK() - q2.getK());

    std::cout << "(q1 * q2):  ";
    (q1 * q2).display();

    assertQuaternionVals(q1 * q2, -25, 11, 3, 55);

    std::cout << "(q1 * 5):  ";
    int tmp = 5;
    (q1 * tmp).display();

    assertQuaternionVals(q1 * tmp, q1.real() * tmp, q1.getI() * tmp, q1.getJ() * tmp, q1.getK() * tmp);

    std::cout << "(q1 == q2):  " << (q1 == q2) << "\n";
    std::cout << "(q1 != q2):  " << (q1 != q2) << "\n";

    assert((q1 == q2) == false);
    assert((q1 != q2) == true);

    auto q3 = q2;

    assertQuaternionVals(q3, q2.real(), q2.getI(), q2.getJ(), q2.getK());

    std::cout << "\nq3 : ";
    q3.display();

    std::cout << "(q2 == q3):  " << (q2 == q3) << "\n";
    std::cout << "(q2 != q3):  " << (q2 != q3) << "\n";

    assert((q2 == q3) == true);
    assert((q2 != q3) == false);
}