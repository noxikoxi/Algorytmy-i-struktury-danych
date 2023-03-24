Projekt zaliczeniowy na algogorytmy i struktury danych
Autor: Tomasz Cach

Temat: Implementacja kwaternionów podobnie do std::complex. 

Zaimplementowanie działania na kwaternionach: 
- dodawanie (operator+),
- odejmowanie (operator-), 
- mnożenie (operator*), 
- sprzężenie, 
- moduł, 
- porównywanie (operator==, operator!=), 
- wyświetlanie.

zawartosc katalogu:
quaternion.h main.cpp Makefile readme.txt

Polecenia Makefile:
- make all -> kompiluje program i tworzy plik wyjsciowy main.out
- make clean -> usuwa pliki wykonywalne i obiektowe

klasa Quaternion
Kwaternion jest przechowywany w postaci a + bi + cj + dk

Składowe klasy:
- a
- i
- j
- k

Przechowują wartości rzeczywiste kwaternionu jak w powyższej sumie

Metody publiczne:
- Quaternion() -> tworzy kwaternion o wszystkich składowych równych 0
- ~Quaternion() -> destruktor, nie musi zwalniać żadnej pamięci, nic nie robi
- Quaternion(T realVal, T iVal, T jVal, T kVal) -> konstruktor tworzy Kwaternion o podanych parametrach
- Quaternion(const Quaternion &q) -> Tworzy kwaternion o takich samuch parametrach jak q
- Quaternion(Quaternion &&q) -> Tworzy kwaternion o takich samych składowych jak q oraz zeruje wszystkie w q
- Quaternion& operator=(const Quaternion &q) -> Przypisuje kwaternionowi wartosci skladowych q
- Quaternion& operator=(Quaternion &&q) -> Przypisuje kwaternionowi wartosci skladowych q i czysci q
- T real() const{return a;} // Zwraca rzeczywista część kwaternionu
- T getI() const{return i;} // Zwraca urojoną część kwaternionu przy i
- T getJ() const{return j;} // Zwraca urojoną część kwaternionu przy j
- T getK() const{return k;} // Zwraca urojoną część kwaternionu przy k
- Quaternion operator+ (const Quaternion &q) const -> zwrace sume dodawancyh kwaternionow
- Quaternion operator- (const Quaternion &q) const -> zwrace różnicę dodawancyh kwaternionow
- Quaternion operator* (const Quaternion &q) const -> zwrace iloczyn dodawancyh kwaternionow
- Quaternion operator* (T val) const -> zwraca wymnożony przez skalar kwaternion
- bool operator== (const Quaternion &q) const -> porównuje kwaterniony i zwraca true, jeżeli są takie same
- bool operator!= (const Quaternion &q) const -> porównuje kwaterniony i zwraca true, jeżeli są różne
- Quaternion conjugate() const -> zwraca sprzężenie kwaternionu
- T norm() const -> zwraca normę kwaternionu
- void display() -> Wyświetla kwaternion jako sumę algebraiczną