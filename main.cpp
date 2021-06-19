#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

struct kontakt {
    int id=0;
    int idUzytkownika=0;
    string imie="",nazwisko="";
    string nr_tel="",adres="",email="";
};

class Uzytkownik {
    int id;
    string nazwa,haslo;
public:
    vector<Uzytkownik> uzytkownicy;

    void aktualizujPlikPoZmianieHasla(vector<Uzytkownik> uzytkownicy) {
        fstream plik;
        int LiczbaUzytkownikow=uzytkownicy.size();
        plik.open("UzytkownicyTymczasowa.txt",ios::out | ios::app);
        if (plik.good() == true) {
            for(int i=0; i<LiczbaUzytkownikow; i++) {
                plik<<uzytkownicy[i].id<<"|";
                plik<<uzytkownicy[i].nazwa<<"|";
                plik<<uzytkownicy[i].haslo<<"|"<<endl;
            }
            plik.close();
            remove("Uzytkownicy.txt");
            rename("UzytkownicyTymczasowa.txt","Uzytkownicy.txt");
        }
    }

    void wczytywanieUzytkownikow(vector<Uzytkownik> &uzytkownicy) {
        fstream plik;
        int DlugoscWczytywanejLinii=0;
        string WczytywanaLinia="";
        Uzytkownik WczytywanyUzytkownik;
        string RozdzielonaLinia="";
        int LiczbaPrzedzielen=0;
        plik.open( "Uzytkownicy.txt", ios::in );
        if (plik.good() == true) {
            while(getline( plik, WczytywanaLinia )) {
                DlugoscWczytywanejLinii=WczytywanaLinia.length();
                for(int j=0; j<DlugoscWczytywanejLinii; j++) {
                    if(WczytywanaLinia[j]=='|') {
                        switch(LiczbaPrzedzielen) {
                        case 0:
                            RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                            WczytywanyUzytkownik.id = atoi(RozdzielonaLinia.c_str());
                            WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                            DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                            LiczbaPrzedzielen++;
                            j=0;
                            break;
                        case 1:
                            RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                            WczytywanyUzytkownik.nazwa = RozdzielonaLinia;
                            WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                            DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                            LiczbaPrzedzielen++;
                            j=0;
                            break;
                        case 2:
                            RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                            WczytywanyUzytkownik.haslo =RozdzielonaLinia;
                            WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                            DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                            LiczbaPrzedzielen=0;
                            uzytkownicy.push_back(WczytywanyUzytkownik);
                            break;
                        }
                    }
                }
            }
            plik.close();
        }
    }

    void rejestracja(vector<Uzytkownik> &uzytkownicy) {
        string nazwa,haslo;
        int iloscUzytkownikow=uzytkownicy.size();
        Uzytkownik DodawanyUzytkownik;
        cout<<"Podaj nazwe uzytkownika: ";
        cin>>nazwa;
        int i=0;
        while(i<iloscUzytkownikow) {
            if(uzytkownicy [i].nazwa==nazwa) {
                cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
                cin>>nazwa;
                i=0;
            } else i++;
        }
        cout<<"Podaj haslo: ";
        cin>>haslo;
        if(iloscUzytkownikow==0)DodawanyUzytkownik.id=1;
        else DodawanyUzytkownik.id=(uzytkownicy[iloscUzytkownikow-1].id+1);
        DodawanyUzytkownik.nazwa=nazwa;
        DodawanyUzytkownik.haslo=haslo;
        fstream plik;
        plik.open("Uzytkownicy.txt",ios::out | ios::app);
        if (plik.good() == true) {
            plik<<DodawanyUzytkownik.id<<"|";
            plik<<DodawanyUzytkownik.nazwa<<"|";
            plik<<DodawanyUzytkownik.haslo<<"|"<<endl;
        } else {
            cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
            system("pause");
        }
        plik.close();
        uzytkownicy.push_back(DodawanyUzytkownik);
        cout<<"Konto zalozone"<<endl;
        Sleep(1000);
    }

    int logowanie(vector<Uzytkownik> uzytkownicy) {
        int iloscUzytkownikow=uzytkownicy.size();
        string nazwa,haslo;
        cout<<"Podaj login: ";
        cin>>nazwa;
        int i=0;
        while(i<iloscUzytkownikow) {
            if(uzytkownicy[i].nazwa==nazwa) {
                for(int proby=0; proby<3; proby++) {
                    cout<<"Podaj haslo. Pozostalo prob "<<3-proby<<": ";
                    cin>>haslo;
                    if (uzytkownicy[i].haslo==haslo) {
                        cout<<"Zalogowales sie."<<endl;
                        Sleep(1000);
                        return uzytkownicy[i].id;
                    }
                }
                cout<<"Podales 3 razy bledne haslo. "<<endl;
                Sleep(3000);
            }
            i++;
        }
        cout<<"Nie ma uzytkownika z takim loginem"<<endl;
        Sleep(1500);
        return 0;
    }

    void zmianaHasla(vector<Uzytkownik> &uzytkownicy,int idZalogowanegoUzytkownika) {
        string haslo;
        int iloscUzytkownikow=uzytkownicy.size();
        cout<<"Podaj nowe haslo: ";
        cin>>haslo;
        for(int i=0; i<iloscUzytkownikow; i++) {
            if(uzytkownicy[i].id==idZalogowanegoUzytkownika) {
                uzytkownicy[i].haslo=haslo;
                cout<<"Haslo zostalo zmienione" <<endl;
                Sleep(1000);
            }
        }
        aktualizujPlikPoZmianieHasla(uzytkownicy);
    }
};

void AktualizujPlikPoEdytowaniu(vector<kontakt> Kontakty,int IteratorAdresata) {
    fstream plik,plik2;
    string WczytywanaLinia="";
    int LiczbaPrzedzielen=0;
    int IdKontaktu=0;
    int IDEdytowanegoAdresata=Kontakty[IteratorAdresata].id;
    string RozdzielonaLinia="";
    plik.open("KsiazkaAdresowaTymczasowa.txt",ios::out | ios::app);
    plik2.open("KsiazkaAdresowa.txt", ios::in );
    if (plik.good() == true) {
        if (plik2.good() == true) {
            while(getline(plik2, WczytywanaLinia)) {
                int DlugoscWczytywanejLinii=WczytywanaLinia.length();
                for(int j=0; j<DlugoscWczytywanejLinii-1; j++) {
                    if(WczytywanaLinia[j]=='|') {
                        switch(LiczbaPrzedzielen) {
                        case 0:
                            RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                            IdKontaktu = atoi(RozdzielonaLinia.c_str());
                            if(IDEdytowanegoAdresata!=IdKontaktu) {
                                plik<<WczytywanaLinia<<endl;
                            } else {
                                plik<<Kontakty[IteratorAdresata].id<<"|";
                                plik<<Kontakty[IteratorAdresata].idUzytkownika<<"|";
                                plik<<Kontakty[IteratorAdresata].imie<<"|";
                                plik<<Kontakty[IteratorAdresata].nazwisko<<"|";
                                plik<<Kontakty[IteratorAdresata].nr_tel<<"|";
                                plik<<Kontakty[IteratorAdresata].adres<<"|";
                                plik<<Kontakty[IteratorAdresata].email<<"|"<<endl;
                            }
                            LiczbaPrzedzielen++;
                            break;
                        case 1:
                            LiczbaPrzedzielen++;
                            break;
                        case 2:
                            LiczbaPrzedzielen++;
                            break;
                        case 3:
                            LiczbaPrzedzielen++;
                            break;
                        case 4:
                            LiczbaPrzedzielen++;
                            break;
                        case 5:
                            LiczbaPrzedzielen++;
                            break;
                        case 6:
                            LiczbaPrzedzielen=0;
                            break;
                        }
                    }
                }
            }
        }
    }
    plik.close();
    plik2.close();
    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowaTymczasowa.txt","KsiazkaAdresowa.txt");
}

void AktualizujPlikPoUsunieciu(vector<kontakt> Kontakty,int IDEdytowanegoAdresata) {
    fstream plik,plik2;
    string WczytywanaLinia="";
    int LiczbaPrzedzielen=0;
    int IdKontaktu=0;
    string RozdzielonaLinia="";
    plik.open("KsiazkaAdresowaTymczasowa.txt",ios::out | ios::app);
    plik2.open("KsiazkaAdresowa.txt", ios::in );
    if (plik.good() == true) {
        if (plik2.good() == true) {
            while(getline(plik2, WczytywanaLinia)) {
                int DlugoscWczytywanejLinii=WczytywanaLinia.length();
                for(int j=0; j<DlugoscWczytywanejLinii-1; j++) {
                    if(WczytywanaLinia[j]=='|') {
                        switch(LiczbaPrzedzielen) {
                        case 0:
                            RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                            IdKontaktu = atoi(RozdzielonaLinia.c_str());
                            if(IDEdytowanegoAdresata!=IdKontaktu) {
                                plik<<WczytywanaLinia<<endl;
                            }
                            LiczbaPrzedzielen++;
                            break;
                        case 1:
                            LiczbaPrzedzielen++;
                            break;
                        case 2:
                            LiczbaPrzedzielen++;
                            break;
                        case 3:
                            LiczbaPrzedzielen++;
                            break;
                        case 4:
                            LiczbaPrzedzielen++;
                            break;
                        case 5:
                            LiczbaPrzedzielen++;
                            break;
                        case 6:
                            LiczbaPrzedzielen=0;
                            break;
                        }
                    }
                }
            }
        }
    }
    plik.close();
    plik2.close();
    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowaTymczasowa.txt","KsiazkaAdresowa.txt");
}

void WyswietlKontakt(kontakt WyswietlanyKontakt) {
    cout<<"Id: "<<WyswietlanyKontakt.id<<endl;
    cout<<"Imie: "<<WyswietlanyKontakt.imie<<endl;
    cout<<"Nazwisko: "<<WyswietlanyKontakt.nazwisko<<endl;
    cout<<"Numer telefonu: "<<WyswietlanyKontakt.nr_tel<<endl;
    cout<<"Adres: "<<WyswietlanyKontakt.adres<<endl;
    cout<<"Adre e-mail: "<<WyswietlanyKontakt.email<<endl;
}

void DodajKontakt(vector<kontakt> &Kontakty,int idZalogowanegoUzytkownika) {
    fstream plik;
    string WczytywanaLinia="";
    int LiczbaPrzedzielen=0;
    string RozdzielonaLinia="";
    int DlugoscWczytywanejLinii;
    string imie,nazwisko,email,adres,nr_tel;
    cout << "Podaj imie: ";
    cin>>imie;
    cout << "Podaj nazwisko: ";
    cin>>nazwisko;
    cout << "Podaj nr telefonu: ";
    cin.sync();
    getline(cin,nr_tel);
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,adres);
    cout << "Podaj e-mail: ";
    cin>>email;
    kontakt DodawanyKontakt;
    int IDOstatniegoKontaktu=0;
    plik.open( "KsiazkaAdresowa.txt", ios::in );
    if (plik.good() == true) {
        while(getline( plik, WczytywanaLinia )) {
            DlugoscWczytywanejLinii=WczytywanaLinia.length();
            for(int j=0; j<DlugoscWczytywanejLinii-1; j++) {
                if(WczytywanaLinia[j]=='|') {
                    switch(LiczbaPrzedzielen) {
                    case 0:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        IDOstatniegoKontaktu = atoi(RozdzielonaLinia.c_str());
                        LiczbaPrzedzielen++;
                        break;
                    case 1:
                        LiczbaPrzedzielen++;
                        break;
                    case 2:
                        LiczbaPrzedzielen++;
                        break;
                    case 3:
                        LiczbaPrzedzielen++;
                        break;
                    case 4:
                        LiczbaPrzedzielen++;
                        break;
                    case 5:
                        LiczbaPrzedzielen++;
                        break;
                    case 6:
                        LiczbaPrzedzielen=0;
                        break;
                    }
                }
            }
        }
    }
    plik.close();
    if(IDOstatniegoKontaktu==0)DodawanyKontakt.id=1;
    else DodawanyKontakt.id=(IDOstatniegoKontaktu+1);
    DodawanyKontakt.idUzytkownika=idZalogowanegoUzytkownika;
    DodawanyKontakt.imie=imie;
    DodawanyKontakt.nazwisko=nazwisko;
    DodawanyKontakt.nr_tel=nr_tel;
    DodawanyKontakt.adres=adres;
    DodawanyKontakt.email=email;
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::app);
    if (plik.good() == true) {
        plik<<DodawanyKontakt.id<<"|";
        plik<<DodawanyKontakt.idUzytkownika<<"|";
        plik<<DodawanyKontakt.imie<<"|";
        plik<<DodawanyKontakt.nazwisko<<"|";
        plik<<DodawanyKontakt.nr_tel<<"|";
        plik<<DodawanyKontakt.adres<<"|";
        plik<<DodawanyKontakt.email<<"|"<<endl;
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    plik.close();
    cout<<"Kontakt dodany.";
    Sleep(1500);
    Kontakty.push_back(DodawanyKontakt);
}

void WczytywanieAdresow(vector<kontakt> &Kontakty,int idZalogowanegoUzytkownika) {
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
                        WczytywanyKontakt.idUzytkownika = atoi(RozdzielonaLinia.c_str());
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 2:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.imie = RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 3:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.nazwisko =RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 4:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.nr_tel = RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 5:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.adres = RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen++;
                        j=0;
                        break;
                    case 6:
                        RozdzielonaLinia=WczytywanaLinia.substr(0,j);
                        WczytywanyKontakt.email = RozdzielonaLinia;
                        WczytywanaLinia=WczytywanaLinia.erase(0,j+1);
                        DlugoscWczytywanejLinii=DlugoscWczytywanejLinii-j-1;
                        LiczbaPrzedzielen=0;
                        if(idZalogowanegoUzytkownika==WczytywanyKontakt.idUzytkownika) {
                            Kontakty.push_back(WczytywanyKontakt);
                        }
                        break;
                    }
                }
            }
        }
        plik.close();
    }
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
            cout<<"Brak kontaktow o takim imieniu"<<endl;
        }
    }
}

void UsunAdresata(vector<kontakt> &Kontakty) {
    int ID=0;
    int LiczbaKontaktow=Kontakty.size();
    char znak;
    int buforID=0;
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
            AktualizujPlikPoUsunieciu(Kontakty,Kontakty[ID].id);
            Kontakty.erase(Kontakty.begin()+ID);
            cout<<"Adresat zostal usuniety"<<endl;
            Sleep(1500);
        }
    } else {
        cout<<"Nie ma adresata o podanym ID"<<endl;
        Sleep(1500);
    }
}

void EdytujAdresata(vector<kontakt> &Kontakty) {
    int ID;
    char WyborParametru;
    int buforID=0;
    int LiczbaKontaktow=Kontakty.size();
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
            AktualizujPlikPoEdytowaniu(Kontakty,ID);
            cout<<"Imie zostalo zmienione."<<endl;
            Sleep(1500);
            break;
        case '2':
            cout<<"Podaj nowe nazwisko adresata :";
            cin>>zmiana;
            Kontakty[ID].nazwisko=zmiana;
            AktualizujPlikPoEdytowaniu(Kontakty,ID);
            cout<<"Nazwisko zostalo zmienione."<<endl;
            Sleep(1500);
            break;
        case '3':
            cout<<"Podaj nowy numer telefonu adresata :";
            cin>>zmiana;
            Kontakty[ID].nr_tel=zmiana;
            AktualizujPlikPoEdytowaniu(Kontakty,ID);
            cout<<"Numer telefonu zostal zmieniony."<<endl;
            Sleep(1500);
            break;
        case '4':
            cout<<"Podaj nowy adres adresata :";
            cin.sync();
            getline(cin,zmiana);
            Kontakty[ID].adres=zmiana;
            AktualizujPlikPoEdytowaniu(Kontakty,ID);
            cout<<"Adres zostal zmieniony."<<endl;
            Sleep(1500);
            break;
        case '5':
            cout<<"Podaj nowy email adresata :";
            cin>>zmiana;
            Kontakty[ID].email=zmiana;
            AktualizujPlikPoEdytowaniu(Kontakty,ID);
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
}

int main() {

    Uzytkownik U1;
    int idZalogowanegoUzytkownika=0;
    U1.wczytywanieUzytkownikow(U1.uzytkownicy);
    vector<kontakt>Kontakty;
    char wybor;
    while(1) {
        if(idZalogowanegoUzytkownika==0) {
            system("cls");
            cout<<"1.Rejestracja"<<endl;
            cout<<"2.Logowanie"<<endl;
            cout<<"9.Koniec Programu"<<endl;
            cin>>wybor;
            if(wybor=='1') {
                    U1.rejestracja(U1.uzytkownicy);
                } else if(wybor=='2') {
                    idZalogowanegoUzytkownika=U1.logowanie(U1.uzytkownicy);
                } else if(wybor=='9') {
                    exit(0);
                }
        } else {
            Kontakty.clear();
            WczytywanieAdresow(Kontakty,idZalogowanegoUzytkownika);
            int LiczbaKontaktow=Kontakty.size();
            char WyborMenuGlowne;
            while(idZalogowanegoUzytkownika!=0) {
                system("cls");
                cout<<"1.Dodaj kontakt"<<endl;
                cout<<"2.Wyszukaj po imieniu"<<endl;
                cout<<"3.Wyszukaj po nazwisku"<<endl;
                cout<<"4.Wyswietl wszystkie kontakty"<<endl;
                cout<<"5.Usun adresata"<<endl;
                cout<<"6.Edytuj adresata"<<endl;
                cout<<"7.Zmien haslo"<<endl;
                cout<<"8.Wyloguj sie"<<endl;
                cin>>WyborMenuGlowne;
                switch(WyborMenuGlowne) {
                case '1':
                    DodajKontakt(Kontakty,idZalogowanegoUzytkownika);
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
                    UsunAdresata(Kontakty);
                    LiczbaKontaktow=Kontakty.size();
                    break;
                case '6':
                    EdytujAdresata(Kontakty);
                    break;
                case '7':
                    U1.zmianaHasla(U1.uzytkownicy,idZalogowanegoUzytkownika);
                    break;
                case '8':
                    idZalogowanegoUzytkownika=0;
                    break;
                }
            }
        }
    }
    return 0;
}

