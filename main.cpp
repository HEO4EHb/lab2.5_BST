//Дана последовательность операций «добавить вершину»,
//«удалить вершину» и «найти ключ» над бинарным деревом поиска.
//Выполнить эти операции.

//Вход
//Во входном файле записана последовательность команд вида “ + x” или “ - x” или “ ? x” или “E”.
//Здесь x – натуральное число не более 10^9. Команда "+x" означает "добавить в дерево число x",
// команда "-x" означает "удалить из дерева число x", команда "?x" - "найти в дереве слово x".
//Команда "E" означает "завершить операции с деревом".
//Каждая команда записана в отдельной строке, начиная с первой позиции, и не содержит пробелов.
//Выход
//В выходной файл запишите результаты выполнения команд "?x" в том порядке, в котором они присутствуют во входном файле.
//Если слово найдено, записать в файл его глубину в дереве, в противном случае - символ 'n'.



#include <iostream>
#include <fstream>
using namespace std;
struct Elem
{
    int data;
    Elem* left;
    Elem* right;
    Elem* parent;
};

Elem* MAKE(int data, Elem* p)// создание древа
{
    Elem* q = new Elem;
    q->data = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}
//добавление элемента
// root это как head
void ADD(int data, Elem*& root)
{
    if (root == nullptr)
    {
        root = MAKE(data, nullptr);
        return;
    }
    Elem* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    Elem* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else
        v->right = u;
}
// обход дерева

Elem* SEARCH(int data, Elem* v)
{
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else
        return SEARCH(data, v->right);
}
void DELETE(int data, Elem*& v, Elem*& root)
{
    Elem* u = SEARCH(data, v);
    if (u == nullptr)
        return;
    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        root = nullptr;
        return;
    }
    if (u->left != nullptr && u->right != nullptr)
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    Elem* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;

}
void PASS(Elem* v)
{
    if (v == nullptr)
        return;
    PASS(v->left);
    cout << v->data << endl;
    PASS(v->right);
}
int DEPTH(data,Elem* v,int meter)
{

if (v == nullptr)
return -1;
if (v->data == data)
return meter;
if (data < v->data)
return DEPTH(data, v->left, meter + 1);
if (data > v->data)
return DEPTH(data, v->right, meter+ 1);

}
void CLEAR(Elem* v)
{
    while (v != nullptr)
    {
        CLEAR(v->left);
        CLEAR(v->right);
        delete v;
    }
}
/*
void CLEAR(Elem*& v)
{
    if (v == nullptr)
        return;
    CLEAR(v->left);
    CLEAR(v->right);
    delete v;
    v = nullptr;
}*/

int main()
{
    Elem* root = nullptr;//начальное значение корня


    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string s;
    int digit = 0;
    int Step = 1;

    while (getline(in, s)) {

        if (s[1] == '9')
            digit = 9;
        else if (s[1] == '8')
            digit = 8;
        else if (s[1] == '7')
            digit = 7;
        else if (s[1] == '6')
            digit = 6;
        else if (s[1] == '5')
            digit = 5;
        else if (s[1] == '4')
            digit = 4;
        else if (s[1] == '3')
            digit = 3;
        else if (s[1] == '2')
            digit = 2;
        else if (s[1] == '1')
            digit = 1;
        else if (s[1] == '0')
            digit = 0;

        if (s[0] == '+')
            ADD(digit, root);
        else if (s[0] == '-')
            DELETE(digit, root);
        else if (s[0] == '?')
        {
            DEPTH(digit, root, Step);//search
            if (DEPTH(digit, root, Step) == -15)
                out << 'n';
            else
                out << DEPTH(digit, root, Step);
        }
        else if (s[0] == 'E')
            break;
    }
    in.close();
    out.close();
    CLEAR(root);
    return 0;
}
