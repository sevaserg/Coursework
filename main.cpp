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



char charbuf[100];

string countrieslist[195];
string purposes[3] = {"common purpose","special purpose","non-postal use"};
string emittypes[4] = {"official","semi-official","non-official","private post"};
string materials[5] = {"plain paper","foil paper","copper","silver","non-listed material"};
string shapes[5] = {"square","triangle","round","rectangle","other"};

struct mark
{
    string country;
    string name;
    char purpose;
    char emittype;
    char shape;
    char material;
    string prestory;
};

class commonfactory
{
    protected:
        mark* m;
        int amt;
    public:
        void deleteall()
        {
            amt = 0;
        }
        virtual void prestory(mark& mk) = 0;
        void setmark(string country)
        {
                amt++;
                if (amt == 1)
                {
                    m = new mark;
                    //-------------------
                    m->country = country;
                    cout<<"Name: ";
                    scanf(" %[^\n]s",charbuf);
                    string buf2(charbuf);
                    m->name = buf2;
                    cout<<"Purpose: "<<endl;
                    for (int i = 0; i < 3; i++) cout<<i+1<<" - "<<purposes[i]<<endl;
                    do{
                        cin>>m->purpose;
                        if (m->purpose<'1'||m->purpose>'3')
                            cout<<"Input error! A single number (1-3) was requested."<<endl;
                    }while(m->purpose<'1'||m->purpose>'3');
                    cout<<"Emitient type: "<<endl;
                    for (int i = 0; i < 4; i++) cout<<i+1<<" - "<<emittypes[i]<<endl;
                    do{
                        cin>>m->emittype;
                        if (m->emittype<'1'||m->emittype>'4')
                            cout<<"Input error! A single number (1-4) was requested."<<endl;
                    }while(m->emittype<'1'||m->emittype>'4');
                    cout<<"Shape: "<<endl;
                    for (int i = 0; i < 5; i++) cout<<i+1<<" - "<<shapes[i]<<endl;
                    do{
                        cin>>m->shape;
                        if (m->shape<'1'||m->shape>'5')
                            cout<<"Input error! A single number (1-5) was requested."<<endl;
                    }while(m->shape<'1'||m->shape>'5');
                    cout<<"Material: "<<endl;
                    for (int i = 0; i < 5; i++) cout<<i+1<<" - "<<materials[i]<<endl;
                    do{
                        cin>>m->material;
                        if (m->material<'1'||m->material>'5')
                            cout<<"Input error! A single number (1-5) was requested."<<endl;
                    }while(m->material<'1'||m->material>'5');
                    prestory(*m);
                }
                else
                {
                    mark* buf = new mark[amt-1];
                    for (int i = 0; i < amt-1; ++i) buf[i] = m[i];
                    m = new mark[amt];
                    for (int i = 0; i < amt-1; ++i) m[i] = buf[i];
                    //------------------------
                    m[amt-1].country = country;
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
                        cin>>m[amt-1].material;
                        if (m[amt-1].material<'1'||m[amt-1].material>'5')
                            cout<<"Input error! A single number (1-5) was requested."<<endl;
                    }while(m[amt-1].material<'1'||m[amt-1].material>'5');
                    prestory(m[amt-1]);
                }
        }

        void getfromfile(mark mk)
        {
            amt++;
                if (amt == 1)
                {
                    m = new mark;
                    //-------------------
                    *m = mk;
                }
                else
                {
                    mark* buf = new mark[amt-1];
                    for (int i = 0; i < amt-1; ++i) buf[i] = m[i];
                    m = new mark[amt];
                    for (int i = 0; i < amt-1; ++i) m[i] = buf[i];
                    //------------------------
                    m[amt-1] = mk;
                }
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
            if (amt > 0)
            {
                if (amt>1)
                {
                    mark* buf = new mark[amt];
                    int j = 0;
                    for (int i = 0; i < amt; ++i)
                    {
                        if (i == mk) j++;
                        buf[i] = m[j];
                        j++;
                    }
                    m = new mark[amt];
                    for (int i = 0;i<amt;++i) m[i] = buf[i];
                    
                }
                else
                {
                    mark buf = m[1-mk];
                    m = new mark;
                    *m = buf;
                }
            }
        }

        void show(int start)
        {
            mark temp;
            if (amt>0)
                for (int i = 0; i < amt; i++)
                {
                    temp = m[i];
                    cout<<i+start<<": "<<temp.name<<", "<<temp.country<< ", made of " << materials[temp.material-'0'-1]
                    <<", for "<<purposes[temp.purpose-'0'-1]<<"."<<endl<<"Emitent type: "<<emittypes[temp.emittype-'0'-1]<<". Shape: "<<shapes[temp.shape-'0'-1]<<". "
                    <<((temp.prestory != "---")?temp.prestory: "")<<endl<<"----------------------------------------------"<<endl;
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
        void prestory(mark& mk)override
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
        void prestory(mark& mk) override
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
        string buf;
    public:
        mainfactory()
        {
            rm = new realmark;
            vm = new virmark;
        }

        void show()
        {
            rm->show(1);
            vm->show(rm->getamt()+1);
        }

        void newmark()
        {
            cout<< "Country: ";
            scanf(" %[^\n]s",charbuf);
            buf = string(charbuf);

            char isreal = '0';
            for (int i = 0;i<195;i++)
                if (buf == countrieslist[i])
                {
                    isreal = '1';
                    break;
                }
            if (isreal == '1') rm->setmark(buf);
            else vm->setmark(buf);
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
                    if (select<rm->getamt()&&select>=0&&rm->getamt()>0)
                    {
                        rm->deletemark(select);
                    }
                    else
                    {
                        if (select-rm->getamt()<vm->getamt()&&select>=0&&vm->getamt())
                        {
                            vm->deletemark(select-rm->getamt());
                        }
                        else
                        {
                            cout<<"Error! No element with number "<<select+1<<"!"<<endl;
                        }
                    }
                }
            }
            else cout<<"No marks are in the list!"<<endl;
        }

        void save()
        {
            ofstream fin;
            fin.open("save.sav",std::ios::out);
            fin<<rm->getamt()<<"\t"<<vm->getamt()<<endl;
            for (int i = 0; i < rm->getamt();++i)
            {
                mark temp = rm->getmark(i);
                fin<<temp.country<<"\t"<<temp.emittype<<"\t"<<temp.material<<"\t"<<temp.name<<"\t"<<temp.prestory<<"\t"<<temp.purpose<<"\t"<<temp.shape<<endl;
            }
            for (int i = 0; i < vm->getamt();++i)
            {
                mark temp = vm->getmark(i);
                fin<<temp.country<<"\t"<<temp.emittype<<"\t"<<temp.material<<"\t"<<temp.name<<"\t"<<temp.prestory<<"\t"<<temp.purpose<<"\t"<<temp.shape<<endl;
            }
            fin.close();
        }
        void load()
        {
            vm->deleteall();
            rm->deleteall();
            int amt1, amt2;
            string t;
            mark temp;
            ifstream fout;
            try
            {
                fout.open("save.sav",std::ios::out);
                getline(fout,t,'\t');
                amt1 = stoi(t);
                getline(fout,t);
                amt2 = stoi(t);
                for (int i = 0; i < amt1; i++)
                {
                    getline(fout,t,'\t'); temp.country = t;
                    getline(fout,t,'\t'); temp.emittype = t[0];
                    getline(fout,t,'\t'); temp.material = t[0];
                    getline(fout,t,'\t'); temp.name = t;
                    getline(fout,t,'\t'); temp.prestory = t;
                    getline(fout,t,'\t'); temp.purpose = t[0];
                    getline(fout,t); temp.shape = t[0];
                    rm->getfromfile(temp);
                }
                for (int i = 0; i < amt2; i++)
                {
                    getline(fout,t,'\t'); temp.country = t;
                    getline(fout,t,'\t'); temp.emittype = t[0];
                    getline(fout,t,'\t'); temp.material = t[0];
                    getline(fout,t,'\t'); temp.name = t;
                    getline(fout,t,'\t'); temp.prestory = t;
                    getline(fout,t,'\t'); temp.purpose = t[0];
                    getline(fout,t); temp.shape = t[0];
                    vm->getfromfile(temp);
                }
                fout.close();
            }
            catch(int error)
            {
                cout<<"Error! File is corrupt or non-existent!"<<endl;
            }
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
        << "6. Real countries list" << endl <<"7. Clear screen" << endl << "0. Quit" << endl;
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
            for (int i = 0; i <195; i++) cout<<i+1<<".\t"<<countrieslist[i]<<endl;
        }break;
        case 7:
        {
            system("cls");
        }break;
        }
        if (choice!=0) cout << "=============================================="<<endl;
    }while (choice !=0);
    return 0;
}
