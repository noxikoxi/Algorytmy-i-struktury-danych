#include <iostream>
#include <vector>
#include <stack>
#include <string> // std::stoi

int rpn(std::vector<std::string> input)
{
    std::stack<int> stos;
    int a,b;
    
    for(auto item : input)
    {
        if(item == "+"){
            a = stos.top();
            stos.pop();
            b = stos.top();
            stos.pop();
            stos.push(b+a);

        }else if(item == "-"){
            a = stos.top();
            stos.pop();
            b = stos.top();
            stos.pop();
            stos.push(b-a);

        }else if(item == "*"){
            a = stos.top();
            stos.pop();
            b = stos.top();
            stos.pop();
            stos.push(b*a);

        }else if(item == "/"){
            a = stos.top();
            stos.pop();
            b = stos.top();
            stos.pop();
            stos.push(b/a);

        }else{ // item to liczba
            stos.push(std::stoi(item));
        }
    }

    return stos.top();
}

template <typename T>
void wypiszVector(std::vector<T> v)
{
    std::cout <<"[ ";
    for(auto item : v)
    {
        std::cout << item << " ";
    }
    std::cout << "]\n";
}

void wypiszWynik(std::vector<std::string> input)
{
    std::cout<<"Dla: ";
    wypiszVector(input);
    std::cout<<"Wynik to: " << rpn(input) << "\n\n";

}

int main()
{
    std::vector<std::string> input1 {"-6", "2", "/"};
    std::vector<std::string> input2 {"2", "7", "+", "3", "/", "14", "3", "-", "4", "*", "+", "2", "/"};
    std::vector<std::string> input3 {"1", "2", "+", "3", "*", "-5", "-3", "-", "/"};
    std::vector<std::string> input4 {"2", "3", "+", "6", "*"};
    
    wypiszWynik(input1);
    wypiszWynik(input2);
    wypiszWynik(input3);
    wypiszWynik(input4);
}