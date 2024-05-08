#include <iostream>
#include <vector> 

using namespace std;

string s1 = "kissa";
string s2;
string s3 = "koira";
vector<string> merkkivektori;

int main()
{
    s3 = move(s1);
    merkkivektori.push_back(s3); // vaihtoehtoisesti move
    cout << "Ennen: " << s1 << endl;
    s1 = move(s2);
    cout << "Jalkeen: " << s1 << endl;
    cout << "Pushbackin jalkeen koiran arvo: " << s3 << endl;
    cout << "Vektorin arvo: " << merkkivektori[0] << endl;
}