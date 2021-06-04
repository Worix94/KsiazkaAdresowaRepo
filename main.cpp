#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

struct kontakt {
    int id=0;
    string imie="",nazwisko="";
    string nr_tel="",adres="",email="";
};

void AktualizujPlikPoUsunieciu(vector<kontakt> Kontakty) {
    fstream plik;
    int LiczbaKontaktow=Kontakty.size();
    plik.open("KsiazkaAdresowaTymczasowa.txt",ios::out | ios::app);
    if (plik.good() == true) {
        for(int i=0; i<LiczbaKontaktow; i++) {
            plik<<Kontakty[i].id<<"|";
            plik<<Kontakty[i].imie<<"|";
            plik<<Kontakty[i].nazwisko<<"|";
            plik<< Kontakty[i].nr_tel<<"|";
            plik<< Kontakty[i].adres<<"|";
            plik<< Kontakty[i].email<<"|"<<endl;
        }
        plik.close();
        remove("KsiazkaAdresowa.txt");
        rename("KsiazkaAdresowaTymczasowa.txt","KsiazkaAdresowa.txt");
        remove("KsiazkaAdresowaTymczasowa.txt");
    }
}

void WyswietlKontakt(kontakt WyswietlanyKontakt) {
    cout<<"Id: "<<WyswietlanyKontakt.id<<endl;
    cout<<"Imie: "<<WyswietlanyKontakt.imie<<endl;
    cout<<"Nazwisko: "<<WyswietlanyKontakt.nazwisko<<endl;
    cout<<"Numer telefonu: "<<WyswietlanyKontakt.nr_tel<<endl;
    cout<<"Adres: "<<WyswietlanyKontakt.adres<<endl;
    cout<<"Adre e-mail: "<<WyswietlanyKontakt.email<<endl;
}

vector<kontakt> DodajKontakt(vector<kontakt> Kontakty) {
    int LiczbaKontaktow=Kontakty.size();
    string imie,nazwisko,email,adres,nr_tel;
    cout << "Podaj imie: ";                  cin>>imie;
    cout << "Podaj nazwisko: ";              cin>>nazwisko;
    cout << "Podaj nr telefonu: ";           cin.sync();getline(cin,nr_tel);
    cout << "Podaj adres: ";                 cin.sync();getline(cin,adres);
    cout << "Podaj e-mail: ";                cin>>email;
    kontakt DodawanyKontakt;
    if(LiczbaKontaktow==0)DodawanyKontakt.id=1;
    else DodawanyKontakt.id=(Kontakty[LiczbaKontaktow-1].id+1);
    DodawanyKontakt.imie=imie;
    DodawanyKontakt.nazwisko=nazwisko;
    DodawanyKontakt.nr_tel=nr_tel;
    DodawanyKontakt.adres=adres;
    DodawanyKontakt.email=email;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::app);
    if (plik.good() == true) {
        plik<<DodawanyKontakt.id<<"|";
        plik<<DodawanyKontakt.imie<<"|";
        plik<<DodawanyKontakt.nazwisko<<"|";
        plik<< DodawanyKontakt.nr_tel<<"|";
        plik<< DodawanyKontakt.adres<<"|";
        plik<< DodawanyKontakt.email<<"|"<<endl;
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    plik.close();
    cout<<"Kontakt dodany.";
    Sleep(1500);
    Kontakty.push_back(DodawanyKontakt);
    return Kontakty;
}

vector<kontakt> WczytywanieAdresow(std::vector<kontakt> Kontakty) {
    fstream plik;
    int DlugoscWczytywanejLinii=0;
    string WczytywanaLinia="";
    kontakt WczytywanyKontakt;
    string RozdzielonaLinia="";
    int LiczbaPrzedzielen=0;
    plik.open( "KsiazkaAdresowa.txt", ios::in );
    if (plik.good() == true) {
        while(getline( plik, WczytywanaLinia )) {
            DlugoscWczytywanejLinii=WczytywanaLinia.length();
            for(int j=0; j<DlugoscWczytywanejLinii; j++) {
                if(WczytywanaLinia[j]=='|') {
                    switch(LiczbaPrzedzielen) {
                    case 0:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.id = atoi(RozdzielonaLinia.c_str());
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 1:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.imie = RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 2:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.nazwisko =RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 3:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.nr_tel = RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 4:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.adres = RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 5:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.email = RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen=0;
                        Kontakty.push_back(WczytywanyKontakt);
                        break;
                    }
                }
            }
        }
        plik.close();
    }
    return Kontakty;
}

void WyszukiwaniePoNazwisku (vector<kontakt> Kontakty) {
    string nazwisko="";
    int LiczbaKontaktow=Kontakty.size();
    int LiczbaKontaktowNiepasujacychDoWyszukania=0;
    cout<<"Podaj nazwisko: ";
    cin>>nazwisko;
    for(int i=0; i<LiczbaKontaktow; i++) {
        if(Kontakty[i].nazwisko==nazwisko) {
            WyswietlKontakt(Kontakty[i]);
        } else LiczbaKontaktowNiepasujacychDoWyszukania++;
        if(LiczbaKontaktowNiepasujacychDoWyszukania>=LiczbaKontaktow) {
            cout<<"Brak kontaktow o takim nazwisku"<<endl;
        }
    }
}

void WyszukiwaniePoImieniu (vector<kontakt> Kontakty) {
    string imie="";
    int LiczbaKontaktowNiepasujacychDoWyszukania=0;
    cout<<"Podaj imie: ";
    cin>>imie;
    int LiczbaKontaktow=Kontakty.size();
    for(int i=0; i<LiczbaKontaktow; i++) {
        if(Kontakty[i].imie==imie) {
            WyswietlKontakt(Kontakty[i]);
        } else LiczbaKontaktowNiepasujacychDoWyszukania++;
        if(LiczbaKontaktowNiepasujacychDoWyszukania>=LiczbaKontaktow) {
            cout<<"Brak kontaktow o takim nazwisku"<<endl;
        }
    }
}

vector<kontakt> UsunAdresata(vector<kontakt> Kontakty) {
    int ID=0;
    int LiczbaKontaktow=Kontakty.size();
    char znak;
    int buforID=0;
    for(int i=0; i<LiczbaKontaktow; i++) {
        WyswietlKontakt(Kontakty[i]);
    }
    cout<<"Usun adresata o ID: ";
    cin>>ID;
    for(int i=0; i<LiczbaKontaktow; i++) {
        if(Kontakty[i].id==ID) ID=i;
        else buforID++;
    }
    if(buforID<LiczbaKontaktow) {
        cout<<endl<<"Jezeli chcesz usunac adresata o podanym numerze ID wcisnij t: ";
        znak=getch();
        if(znak=='t') {
            Kontakty.erase(Kontakty.begin()+ID);
            AktualizujPlikPoUsunieciu(Kontakty);
            cout<<"Adresat zosta³ usuniety"<<endl;
            Sleep(1500);
        }
    } else {
        cout<<"Nie ma adresata o podanym ID"<<endl;
        Sleep(1500);
    }

    return Kontakty;
}

vector<kontakt> EdytujAdresata(std::vector<kontakt> Kontakty) {
    int ID;
    char WyborParametru;
    int buforID=0;
    int LiczbaKontaktow=Kontakty.size();
    for(int i=0; i<LiczbaKontaktow; i++) {
        WyswietlKontakt(Kontakty[i]);
    }
    cout<<"Podaj ID adresata, ktorego chcesz edytowac :";
    cin>>ID;
    string zmiana;
    for(int i=0; i<LiczbaKontaktow; i++) {
        if(Kontakty[i].id==ID) ID=i;
        else buforID++;
    }
    if(buforID<LiczbaKontaktow) {
        system("cls");
        cout<<"Edytuj: "<<endl;
        cout<<"1.Imie"<<endl;
        cout<<"2.Nazwisko"<<endl;
        cout<<"3.Numer telefonu"<<endl;
        cout<<"4.Adres"<<endl;
        cout<<"5.Email"<<endl;
        cout<<"6.Powrot do menu"<<endl;
        cin>>WyborParametru;
        switch(WyborParametru) {
        case '1':
            cout<<"Podaj nowe imie adresata :";
            cin>>zmiana;
            Kontakty[ID].imie=zmiana;
            AktualizujPlikPoUsunieciu(Kontakty);
            cout<<"Imie zostalo zmienione."<<endl;
            Sleep(1500);
            break;
        case '2':
            cout<<"Podaj nowe nazwisko adresata :";
            cin>>zmiana;
            Kontakty[ID].nazwisko=zmiana;
            AktualizujPlikPoUsunieciu(Kontakty);
            cout<<"Nazwisko zostalo zmienione."<<endl;
            Sleep(1500);
            break;
        case '3':
            cout<<"Podaj nowy numer telefonu adresata :";
            cin>>zmiana;
            Kontakty[ID].nr_tel=zmiana;
            AktualizujPlikPoUsunieciu(Kontakty);
            cout<<"Numer telefonu zostal zmieniony."<<endl;
            Sleep(1500);
            break;
        case '4':
            cout<<"Podaj nowy adres adresata :";
            cin.sync();
            getline(cin,zmiana);
            Kontakty[ID].adres=zmiana;
            AktualizujPlikPoUsunieciu(Kontakty);
            cout<<"Adres zostal zmieniony."<<endl;
            Sleep(1500);
            break;
        case '5':
            cout<<"Podaj nowy email adresata :";
            cin>>zmiana;
            Kontakty[ID].email=zmiana;
            AktualizujPlikPoUsunieciu(Kontakty);
            cout<<"Email zostal zmieniony."<<endl;
            Sleep(1500);
            break;
        case '6':
            break;
        }
    } else {
        cout<<"Nie ma adresata o podanym ID"<<endl;
        Sleep(1500);
    }
    return Kontakty;
}

int main() {
    vector<kontakt>Kontakty;
    Kontakty=WczytywanieAdresow(Kontakty);
    int LiczbaKontaktow=Kontakty.size();
    char WyborMenuGlowne;
    while(1) {
        {
            system("cls");
            cout<<"1.Dodaj kontakt"<<endl;
            cout<<"2.Wyszukaj po imieniu"<<endl;
            cout<<"3.Wyszukaj po nazwisku"<<endl;
            cout<<"4.Wyswietl wszystkie kontakty"<<endl;
            cout<<"5.Usun adresata"<<endl;
            cout<<"6.Edytuj adresata"<<endl;
            cout<<"9.Zakoncz program"<<endl;
            cin>>WyborMenuGlowne;
            switch(WyborMenuGlowne) {
            case '1':
                Kontakty=DodajKontakt(Kontakty);
                LiczbaKontaktow=Kontakty.size();
                break;
            case '2':
                WyszukiwaniePoImieniu(Kontakty);
                cout<<"Wcisnij enter aby kontynuowac...";
                getch();
                break;
            case '3':
                WyszukiwaniePoNazwisku(Kontakty);
                cout<<"Wcisnij enter aby kontynuowac...";
                getch();
                break;
            case '4':

                for(int i=0; i<LiczbaKontaktow; i++) {
                    WyswietlKontakt(Kontakty[i]);
                }
                cout<<"Wcisnij enter aby kontynuowac...";
                getch();
                break;
            case '5':
                Kontakty=UsunAdresata(Kontakty);
                LiczbaKontaktow=Kontakty.size();
                break;
            case '6':
                Kontakty=EdytujAdresata(Kontakty);
                break;
            case '9':
                exit(0);
            }
        }
    }
    return 0;
}

