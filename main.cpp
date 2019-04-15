/*
Создать сборник марок, который может включать в себя марки реальных государств и виртуальных государств.
Пользователь может выбирать, какие марки необходимо добавить в сборник (характеристики марок: к какому
государству относятся, назначение, по характеру эмитента,  форма, материал), и в каком количестве.
Использовать паттерн «Абстрактная фабрика». Результат создания сборника марок и их характеристики
записываются в выходной файл, разделенный по типам марок – реальное государство или нет. Пользователь
может загрузить сборник марок из файла.
*/

#include <windows.h>

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

string countrieslist[195];

char charbuf[100];

string materials[5] = {"plain paper","foil paper","copper","silver","non-listed material"};
string shapes[5] = {"square","triangle","round","rectangle","other"};
string purposes[3] = {"common purpose","special purpose","non-postal use"};
string emittypes[4] = {"official","semi-official","non-official","private post"};

struct mark
{
    string country;
    string name;
    char purpose;
    char emittype;
    char shape;
    char material;
    string amount;
    string prestory;
};

class commonfactory
{
protected:
    mark* m;
    int amt;
public:
    virtual void prestory(mark &k) = 0;
    void setmark(string country)
    {
        mark* buf = new mark[amt];
        for (int i = 0; i < amt; i++) buf[i] = m[i];
        amt=amt+1;
        mark* m = new mark[amt];
        for (int i = 0; i < amt-1; i++) m[i] = buf[i];
        m[amt-1].country = country;
        delete[]buf;
        cout<<"Name: ";
        scanf(" %[^\n]s",charbuf);
        string buf2(charbuf);
        m[amt-1].name = buf2;
        cout<<"Purpose: "<<endl;
        for (int i = 0; i < 3; i++) cout<<i+1<<" - "<<purposes[i]<<endl;
        do{
            cin>>m[amt-1].purpose;
            if (m[amt-1].purpose<'1'||m[amt-1].purpose>'3')
                cout<<"Input error! A single number (1-3) was requested."<<endl;
        }while(m[amt-1].purpose<'1'||m[amt-1].purpose>'3');
        cout<<"Emitient type: "<<endl;
        for (int i = 0; i < 4; i++) cout<<i+1<<" - "<<emittypes[i]<<endl;
        do{
            cin>>m[amt-1].emittype;
            if (m[amt-1].emittype<'1'||m[amt-1].emittype>'4')
                cout<<"Input error! A single number (1-4) was requested."<<endl;
        }while(m[amt-1].emittype<'1'||m[amt-1].emittype>'4');
        cout<<"Shape: "<<endl;
        for (int i = 0; i < 5; i++) cout<<i+1<<" - "<<shapes[i]<<endl;
        do{
            cin>>m[amt-1].shape;
            if (m[amt-1].shape<'1'||m[amt-1].shape>'5')
                cout<<"Input error! A single number (1-5) was requested."<<endl;
        }while(m[amt-1].shape<'1'||m[amt-1].shape>'5');
        cout<<"Material: "<<endl;
        for (int i = 0; i < 5; i++) cout<<i+1<<" - "<<materials[i]<<endl;
        do{
            cin>>m[amt-1].shape;
            if (m[amt-1].shape<'1'||m[amt-1].shape>'5')
                cout<<"Input error! A single number (1-5) was requested."<<endl;
        }while(m[amt-1].shape<'1'||m[amt-1].shape>'5');
        prestory(m[amt-1]);
    }

    int getamt()
    {
        return amt;
    }

    mark getmark(int num)
    {
        return m[num];
    }

    void deletemark(int mk)
    {
        amt--;
        int j = 0;
        mark* buf = new mark[amt];
        for (int i = 0; i < amt; i++)
        {
            if (j == mk) j++;
            buf[i] = m[j];
            j++;
        }
        m = new mark[amt];
        for (int i = 0; i < amt; i++) m[i] = buf[i];
        delete[]buf;
    }

    void show(int start)
    {

        mark temp;
        if (amt>0)
            for (int i = 0; i < amt; i++)
            {
                temp = m[i];
                cout<<"1";
                cout<<i+start<<": "<<temp.name<<", "<<temp.country<< ", "<<temp.amount << ((temp.amount == "1") ? " piece. Made of " : " pcs. Made of ") << materials[temp.material-'0'-1]
                <<", for "<<purposes[temp.purpose-'0'-1]<<"."<<endl<<"Emitent type: "<<emittypes[temp.emittype-'0'-1]<<". Shape: "<<shapes[temp.shape-'0'-1]<<". "
                <<((temp.prestory == "---")?temp.prestory: "")<<endl<<"----------------------------------------------"<<endl;
            }
    }
};

class realmark : public commonfactory
{
public:

    realmark()
    {
        amt = 0;
    }
    void prestory(mark& mk)
    {
        cout<<"Pre-story(if not needed, type three '-' symbols): ";
        scanf(" %[^\n]s",charbuf);
        string buf3(charbuf);
        mk.prestory=buf3;
    }
    ~realmark()
    {
        delete[]m;
    }
};

class virmark : public commonfactory
{
public:
    virmark()
    {
        amt = 0;
    }
    void prestory(mark& mk)
    {
        mk.prestory = "---";
    }
    ~virmark()
    {
        delete[]m;
    }
};

class mainfactory
{
private:
    virmark* vm;
    realmark* rm;
    string* buf;
public:
    mainfactory()
    {
        rm = new realmark;
        vm = new virmark;
    }

    void show()
    {
        /*mark temp;
        if (rm->getamt()>0)
        for (int i = 0; i < rm->getamt();i++)
        {
            cout<<"1";
            temp = rm->getmark(i);
            cout<<i+1<<": "<<temp.name<<", "<<temp.country<< ", "<<temp.amount << ((temp.amount == "1") ? " piece. Made of " : " pcs. Made of ") << materials[temp.material-'0'-1]
            <<", for "<<purposes[temp.purpose-'0'-1]<<"."<<endl<<"Emitent type: "<<emittypes[temp.emittype-'0'-1]<<". Shape: "<<shapes[temp.shape-'0'-1]<<". "
            <<((temp.prestory == "---")?temp.prestory: "")<<endl<<"----------------------------------------------"<<endl;
        }*/
        rm->show(1);
        vm->show(rm->getamt());

    }

    void newmark()
    {
        cout<< "Country: ";
        scanf(" %[^\n]s",charbuf);
        buf = new string(charbuf);
        //string buf(k);
        char isreal = '0';
        for (int i = 0;i<195;i++)
            if (*buf == countrieslist[i])
            {
                isreal = '1';
                break;
            }
        if (isreal == '1') rm->setmark(*buf);
        else vm->setmark(*buf);
    }

    void deletemark()
    {
        int select;
        if (rm->getamt()>0 || vm->getamt()>0)
        {
            cout<< "Put in number from 1 to " << rm->getamt()+vm->getamt() <<", 0 to abort: ";
            cin>>select;
            if (select!=0)
            {
                select--;
                if (select<rm->getamt()&&select>0)
                {
                    rm->deletemark(select);
                }
                else
                {
                    if (select-rm->getamt()<vm->getamt()&&select>0)
                    {
                        rm->deletemark(select-rm->getamt());
                    }
                    else cout<<"Error! No element with number "<<select+1<<"!"<<endl;

                }
            }
        }
    }

    void save()
    {

    }
    void load()
    {

    }
};

int main()
{
    int choice;
    mainfactory* fact = new mainfactory;
    ifstream fst;
    fst.open("clist.txt");
    for (int i = 0; i < 195; i++)
        getline(fst,countrieslist[i]);
    do{
        cout << "1. New mark" << endl << "2. Delete mark" << endl << "3. Load from file" << endl << "4. Save in file" << endl << "5. View marks" << endl
        << "6. Real countries list" << endl << "0. Quit" << endl;
        cin >> choice;
        cout << "=============================================="<<endl;
        switch(choice)
        {
        case 1:
        {
            fact->newmark();
        }break;
        case 2:
        {
            fact->deletemark();
        }break;
        case 3:
        {
            fact->load();
        }break;
        case 4:
        {
            fact->save();
        }break;
        case 5:
        {
            fact->show();
        }break;
        case 6:
        {
            for (int i = 0; i <195; i++) cout<<i+1<<". "<<countrieslist[i]<<endl;
        }break;
        }
        if (choice!=0) cout << "=============================================="<<endl;
    }while (choice !=0);
    return 0;
}
