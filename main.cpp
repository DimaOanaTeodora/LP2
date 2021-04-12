#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

ifstream fin("input.in");

//CLASS DATA

class Data {
    int zi, an;
    char *luna;
public:
    Data();

    Data(const Data &);

    Data(int zi, const char *luna, int an);

    ~Data();

    int get_zi();

    int get_an();

    char *get_luna();

    Data &operator=(const Data &data);

    friend istream &operator>>(istream &, Data &);

    friend ostream &operator<<(ostream &, Data &);
};

Data::Data() {
    zi = 0;
    an = 0;
    luna = new char[20];
}

Data::~Data() {
    delete[] luna;
    luna = NULL;
}

Data::Data(const Data &data) {
    this->luna = new char[20];
    this->zi = data.zi;
    this->an = data.an;
    strcpy(this->luna, data.luna);
}

Data::Data(int zi, const char *luna, int an) {
    this->luna = new char[20];
    this->zi = zi;
    this->an = an;
    strcpy(this->luna, luna);
}

int Data::get_an() {
    return this->an;
}

int Data::get_zi() {
    return this->zi;
}

char *Data::get_luna() {
    return this->luna;
}

Data &Data::operator=(const Data &data) {
    this->zi = data.zi;
    this->an = data.an;
    if (data.luna == NULL) {
        char *del = this->luna;
        delete[] del;
        this->luna = NULL;
    } else {
        strcpy(this->luna, data.luna);
    }
}

istream &operator>>(istream &in, Data &x) {
    in >> x.zi;
    in.get();
    in.getline(x.luna, 20);
    for (int i = 0; i < strlen(x.luna); i++) {
        x.luna[i] = (char) toupper(x.luna[i]);
    }
    in >> x.an;
    return in;
}

ostream &operator<<(ostream &out, Data &x) {
    out << x.zi << "/" << x.luna << "/" << x.an;
    return out;
}



//CLASS ANGAJAT

class Angajat {
protected:
    char *nume, *prenume;
    float salariu;
    Data data_angajare;
    static int luna_curenta, an_curent;
public:
    static void init_an_luna(int an, int luna);

    Angajat();

    Angajat(const Angajat &angajat);

    Angajat(char *nume, char *prenume, float salariu, Data data);

    virtual ~Angajat();

    virtual float solve_salariu(float) = 0;

    int get_vechime();

    Angajat &operator=(const Angajat &angajat);

    virtual void citire(istream &in);

    virtual void afis(ostream &out);

    friend istream &operator>>(istream &, Angajat &);

    friend ostream &operator<<(ostream &, Angajat &);
};

void Angajat::init_an_luna(int an, int luna) {
    an_curent = an;
    luna_curenta = luna;
}

Angajat::Angajat() {
    nume = new char[20];
    prenume = new char[30];
}

Angajat::Angajat(const Angajat &angajat) {
    this->nume = new char[20];
    this->prenume = new char[30];
    this->salariu = angajat.salariu;
    strcpy(this->nume, angajat.nume);
    strcpy(this->prenume, angajat.prenume);
    this->data_angajare = angajat.data_angajare;
}

Angajat::Angajat(char *nume, char *prenume, float salariu, Data data) {
    this->nume = new char[20];
    this->prenume = new char[30];
    strcpy(this->nume, nume);
    strcpy(this->prenume, prenume);
    this->salariu = salariu;
    this->data_angajare = data;
}

Angajat::~Angajat() {
    delete[] nume;
    nume = NULL;
    delete[] prenume;
    prenume = NULL;
}

int Angajat::get_vechime() {
    int nr_luna = 0;
    if (strcmp(this->data_angajare.get_luna(), "DECEMRBIE") == 0) nr_luna = 12;
    if (strcmp(this->data_angajare.get_luna(), "NOIEMBRIE") == 0) nr_luna = 11;
    if (strcmp(this->data_angajare.get_luna(), "OCTOMBRIE") == 0) nr_luna = 10;
    if (strcmp(this->data_angajare.get_luna(), "SEPTEMBRIE") == 0) nr_luna = 9;
    if (strcmp(this->data_angajare.get_luna(), "AUGUST") == 0) nr_luna = 8;
    if (strcmp(this->data_angajare.get_luna(), "IULIE") == 0) nr_luna = 7;
    if (strcmp(this->data_angajare.get_luna(), "IUNIE") == 0) nr_luna = 6;
    if (strcmp(this->data_angajare.get_luna(), "MAI") == 0) nr_luna = 5;
    if (strcmp(this->data_angajare.get_luna(), "APRILIE") == 0) nr_luna = 4;
    if (strcmp(this->data_angajare.get_luna(), "MARTIE") == 0) nr_luna = 3;
    if (strcmp(this->data_angajare.get_luna(), "FEBRUARIE") == 0) nr_luna = 2;
    if (strcmp(this->data_angajare.get_luna(), "IANUARIE") == 0) nr_luna = 1;
    if (nr_luna == 0) {
        cout << "ATI INTRODUS NUMELE LUNII GRESIT\n\n EROARE!\n\n EROARE!!!!!\n";
        return 0;
    }
    int nrluni = (an_curent - this->data_angajare.get_an()) * 12 + luna_curenta - nr_luna;
    return (int) (nrluni / 12);
}

Angajat &Angajat::operator=(const Angajat &angajat) {
    this->salariu = angajat.salariu;
    this->data_angajare = angajat.data_angajare;
    if (angajat.nume == NULL) {
        char *del = this->nume;
        delete[] del;
        this->nume = NULL;
        char *dilit = this->prenume;
        delete[] dilit;
        this->prenume = NULL;
    } else {
        strcpy(this->nume, angajat.nume);
        strcpy(this->prenume, angajat.prenume);
    }
}

void Angajat::citire(istream &in) {
    in.get();
    in.getline(this->nume, 20);
    in.getline(this->prenume, 30);
    in >> this->salariu;
    in >> this->data_angajare;
}

void Angajat::afis(ostream &out) {
    out << "Numele complet al angajatului este " << this->nume << " " << this->prenume;
    out << ", iar acesta are salariu de " << this->salariu << ". A fost angajat in data de ";
    out << this->data_angajare << ".";
}

istream &operator>>(istream &in, Angajat &angajat) {
    angajat.citire(in);
    return in;
}

ostream &operator<<(ostream &out, Angajat &angajat) {
    angajat.afis(out);
    return out;
}



//CLASS PART TIME DERIVATA DIN ANGAJAT

class Part_Time : public Angajat {
    int nr_ore_zi;
    Data final_contract;
public:
    Part_Time();

    Part_Time(const Part_Time &part_time) : Angajat(part_time) {
        this->nr_ore_zi = part_time.nr_ore_zi;
        this->final_contract = part_time.final_contract;
    }

    Part_Time(const char *nume, const char *prenume, float salariu, Data data_angajare, int nr_ore, Data data_final);

    ~Part_Time();

    float solve_salariu(float);

    Part_Time &operator=(const Part_Time &part_time);

    void citire(istream &in);

    void afis(ostream &out);

    friend istream &operator>>(istream &, Part_Time &);

    friend ostream &operator<<(ostream &, Part_Time &);
};

Part_Time::Part_Time() {
    nr_ore_zi = 0;
}

Part_Time::Part_Time(const char *nume, const char *prenume, float salariu, const Data data_angajare, int nr_ore,
                     Data data_final) {
    this->nume = new char[20];
    this->prenume = new char[30];
    strcpy(this->nume, nume);
    strcpy(this->prenume, prenume);
    this->salariu = salariu;
    this->data_angajare = data_angajare;
    this->nr_ore_zi = nr_ore;
    this->final_contract = data_final;
}

Part_Time::~Part_Time() {
    if (nume != NULL) {
        delete[] nume;
        delete[] prenume;
    }
    nume = NULL;
    prenume = NULL;
}

float Part_Time::solve_salariu(float prima) {
    int ok = 0;
    if (this->final_contract.get_an() > 2021)ok = 1;
    if (this->final_contract.get_an() == 2021 && strcmp(this->final_contract.get_luna(), "APRILIE") > 0) ok = 1;
    if (ok == 1)
        return this->salariu + prima;
    else
        return this->salariu + (float) (0.75 * prima);
}

Part_Time &Part_Time::operator=(const Part_Time &part_time) {
    Angajat::operator=(part_time);
    this->nr_ore_zi = part_time.nr_ore_zi;
    this->final_contract = part_time.final_contract;
    return *this;
}

void Part_Time::citire(istream &in) {
    Angajat::citire(in);
    in >> this->nr_ore_zi;
    in >> this->final_contract;
}

void Part_Time::afis(ostream &out) {
    Angajat::afis(out);
    out << " Lucreaza " << this->nr_ore_zi << " ore pe zi si constractul sau de munca se incheie in data de ";
    out << this->data_angajare << ".";
}

istream &operator>>(istream &in, Part_Time &part_time) {
    part_time.citire(in);
    return in;
}

ostream &operator<<(ostream &out, Part_Time &part_time) {
    part_time.afis(out);
    return out;
}



//CLASS PERMANENT DERIVATA DIN ANGAJAT

class Permanent : public Angajat {
    int nr_minori_intretinere;
public:
    Permanent();

    Permanent(const Permanent &permanent) : Angajat(permanent) {
        this->nr_minori_intretinere = permanent.nr_minori_intretinere;
    }

    Permanent(const char *nume, const char *prenume, float salariu, const Data data_angajare, int nr_minori);

    ~Permanent();

    float solve_salariu(float);

    Permanent &operator=(const Permanent &permanent);

    void citire(istream &in);

    void afis(ostream &out);

    friend istream &operator>>(istream &, Permanent &);

    friend ostream &operator<<(ostream &, Permanent &);
};

Permanent::Permanent() {
    nr_minori_intretinere = 0;
}

Permanent::Permanent(const char *nume, const char *prenume, float salariu, const Data data_angajare, int nr_minori) {
    this->nume = new char[20];
    this->prenume = new char[30];
    strcpy(this->nume, nume);
    strcpy(this->prenume, prenume);
    this->salariu = salariu;
    this->data_angajare = data_angajare;
    this->nr_minori_intretinere = nr_minori;
}

Permanent::~Permanent() {
    nr_minori_intretinere = 0;
}

float Permanent::solve_salariu(float prima) {
    return this->salariu + (float) (this->nr_minori_intretinere * this->get_vechime() * 0.01 * prima);
}

Permanent &Permanent::operator=(const Permanent &permanent) {
    Angajat::operator=(permanent);
    this->nr_minori_intretinere = permanent.nr_minori_intretinere;
    return *this;
}

void Permanent::citire(istream &in) {
    Angajat::citire(in);
    in >> this->nr_minori_intretinere;
}

void Permanent::afis(ostream &out) {
    Angajat::afis(out);
    out << "Acesta are " << this->nr_minori_intretinere << " minori in intretinere. ";
}

istream &operator>>(istream &in, Permanent &permanent) {
    permanent.citire(in);
    return in;
}

ostream &operator<<(ostream &out, Permanent &permanent) {
    permanent.afis(out);
    return out;
}


void meniu() {
    cout << " Ce doriti sa faceti?\n";
    cout << "1.Afisarea tuturor salariilor angajatilor\n";
    cout << "2.Afisarea unui salariat in functie de numarul de ordine\n";
    cout << "3.Adaugarea unui nou angajat\n";
    cout << "4.Stergerea unui angajat existent in functie de numarul de ordine\n";
    cout << "5.Iesire/Inchidere program\n";
    cout << "INTRODUCETI OPTIUNEA DORITA ( DE LA 1 LA 5 )...";
}

int tip_angajat() {
    int optiune_angajat;
    cout << "Angajatul este part time (1) sau permanent(2) ? Introduceti 1 sau 2 ... ";
    do {
        cin >> optiune_angajat;
    } while (optiune_angajat != 1 && optiune_angajat != 2);
    return optiune_angajat;
}

int nr_ordine_angajat(int n, int m) {
    int optiune_angajat = tip_angajat();
    cout << "Introduceti numarul de ordine al angajatului ";
    if (optiune_angajat == 2)cout << "permanent ales . De la 1 la " << m << "...";
    else cout << "part time ales . De la 1 la " << n << "...";
    int nr_ordine;
    if (optiune_angajat == 1) {
        do {
            cin >> nr_ordine;
        } while (nr_ordine < 1 && nr_ordine > n);
    } else {
        do {
            cin >> nr_ordine;
        } while (nr_ordine < 1 && nr_ordine > m);
    }
    return nr_ordine;
}

/*
void afis_salariat(int m, int n, Part_Time part_time[10], Permanent permanent[10]) {
    int optiune_angajat;
    optiune_angajat = tip_angajat();
    int nr_ordine = nr_ordine_angajat(n, m);
    if (optiune_angajat == 1)cout << part_time[nr_ordine];//////////////////////////////
    else cout << permanent[nr_ordine];///////////////////
}

void stergere_angajat(int m, int n, Part_Time part_time[10], Permanent permanent[10]) {
    int optiune_angajat = tip_angajat();
    int nr_ordine = nr_ordine_angajat(n, m);
    int i;
    if (optiune_angajat == 1) {
        for (i = nr_ordine; i < n; i++)
            part_time[i] = part_time[i + 1];
    } else {
        for (i = nr_ordine; i < m; i++)
            permanent[i] = permanent[i + 1];
    }
    cout << "Ati sters angajatul! Felicitari!\n";
}
*/
int Angajat::luna_curenta, Angajat::an_curent;

int main() {
    Angajat::init_an_luna(2021, 4);
    int opt, n, i,tip_angajat;
    
    float prima_firma;
    cout << "PRIMA FIRMEI ESTE =";
    cin >> prima_firma;
    //fin >> n;
    n=1;
    cout<<"Acum se citesc cei "<<n<<" angajati din fisier. Va rugam asteptati...";
    // nu te lasa sa faci asta pt ca e clasa abstracta si 
    //tu cand faci new Angajat[n] practic instantiezi de n ori 
    // clasa Angajat ceea ce nu ai voie sa faci pe o clasa abstracta
    // trebuie sa faci un vector de pointeri ( ca tu practic sa faci upcasting )
    Angajat *angajati[n]; //declar un vector de pointeri catre Angajat nu de obiecte(instante angajat)
    for(i=1;i<=n;i++)
    {
        //PS1: nu ai treaba cu downcasting-ul la citire 
        //Recomad: Pentru un mai bun control al erorilor pana il definitivezi 
        //sa lasi citirea datelor de la tastatura nu din fisier
        // PS2: eu n-am reusit sa-ti verific citirea din cauza fisierului insa de compilat compileaza
        // de aceea e possibil sa mai ai probelme la citire pe care eu sa nu le pot vedea
        
        //downcastingul se foloseste cand vrei sa treci de la un pointer
        // de tipul clasei de baza la ceva de tipul derivat 
        //o sa lucrezi cu downcastingul cred ca la tema urmatoare cand o sa ai 
        //niste metode suprascrise si vei avea nevoie sa le accesezi 
        //pe cele din clasa derivata nu din clasa de baza
        
        Angajat *angajat; // vectorul tau are pointeri de tip angajat pe care se face upcasting
        //fin>>tip_angajat;//aici trebuie sa citesc angajati in general ori de tip part time ori de tip permanent si nu stiu cum sa citesc.
        cin>>tip_angajat;
        if(tip_angajat==1)//inseamna ca angajatul citit e de tip part time
        {
           angajat =new Part_Time(); // echivalent cu Angajat * angajat = new Part_Time ();
            cin>>(*angajat); //practic tu aici citesti obiectul catre care pointeaza *angajat
            // de aceea am pus * ca tu vrei sa scrii in memorie 
            // pointerul tau e doar o adresa catre acea zona de memorie
            // pe care tu vrei sa o accesezi la scriere
            // de aceea (*p) iti acceseaza zona de memorie pe care o "arata" p 
        }
        if(tip_angajat==2)//inseamna ca angajatul citit e de tip permanent
        {
            //nimic
            angajat =new Permanent();
            cin>>(*angajat);

        }
    }
    do {
        meniu();
        cin >> opt;
        switch (opt) {
            case 1: {

                break;
            }
            case 2:
                //afis_salariat(m, n, part_time, permanent);
                break;
            case 3: {
                /*optiune_angajat = tip_angajat();
                if (optiune_angajat == 2) {
                    cin >> permanent[n + 1];////////////////
                    n++;
                } else {
                    cin >> part_time[m + 1];//trebuie implementata citirea
                    m++;
                }
                cout << "Ati introdus angajatul! Felicitari!\n";*/
                break;
            }
            case 4:
                //stergere_angajat(m, n, part_time, permanent);
                break;
            case 5:
                return 0;
            default:
                cout << "OPTIUNE GRESITA, MAI INCERCATI O DATA !\n";
                break;
        }
    } while (opt != 5);
    cout << "O zi buna !";
    return 0;
}
