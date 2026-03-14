#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_CLIENTS = 100;
const int MAX_CHAMBRES = 50;
const int MAX_RESERVATIONS = 200;

class Client {
private:
    int id;
    string nom;
    string contact;

public:
    Client();
    Client(int, string, string);

    int getId();
    string getNom();
    string getContact();

    void afficher();
    void saisir();
};

Client::Client() {
    id = 0;
    nom = "";
    contact = "";
}

Client::Client(int i, string n, string c) {
    id = i;
    nom = n;
    contact = c;
}

int Client::getId() { return id; }
string Client::getNom() { return nom; }
string Client::getContact() { return contact; }

void Client::afficher() {
    cout << "ID: " << id << " | Nom: " << nom << " | Contact: " << contact << endl;
}

void Client::saisir() {
    cout << "ID client: ";
    cin >> id;
    cout << "Nom: ";
    cin >> nom;
    cout << "Contact: ";
    cin >> contact;
}

class Chambre {
private:
    int numero;
    string type;
    double prix;
    bool dispo;

public:
    Chambre();
    Chambre(int, string, double, bool);

    int getNumero();
    string getType();
    double getPrix();
    bool estDispo();
    void setDispo(bool);

    void afficher();
    void saisir();
};

Chambre::Chambre() {
    numero = 0;
    type = "";
    prix = 0.0;
    dispo = true;
}

Chambre::Chambre(int n, string t, double p, bool d) {
    numero = n;
    type = t;
    prix = p;
    dispo = d;
}

int Chambre::getNumero() { return numero; }
string Chambre::getType() { return type; }
double Chambre::getPrix() { return prix; }
bool Chambre::estDispo() { return dispo; }
void Chambre::setDispo(bool d) { dispo = d; }

void Chambre::afficher() {
    cout << "Chambre " << numero << " | Type: " << type << " | Prix: " << prix
         << " | Disponible: " << (dispo ? "Oui" : "Non") << endl;
}

void Chambre::saisir() {
    cout << "Numero chambre: ";
    cin >> numero;
    cout << "Type (simple/double): ";
    cin >> type;
    cout << "Prix: ";
    cin >> prix;
    dispo = true;
}

class Reservation {
private:
    int idR;
    int idC;
    int numCh;
    string date;

public:
    Reservation();
    Reservation(int, int, int, string);

    int getIdR();
    int getIdC();
    int getNumCh();
    string getDate();

    void afficher();
    void saisir();
};

Reservation::Reservation() {
    idR = 0;
    idC = 0;
    numCh = 0;
    date = "";
}

Reservation::Reservation(int r, int c, int n, string d) {
    idR = r;
    idC = c;
    numCh = n;
    date = d;
}

int Reservation::getIdR() { return idR; }
int Reservation::getIdC() { return idC; }
int Reservation::getNumCh() { return numCh; }
string Reservation::getDate() { return date; }

void Reservation::afficher() {
    cout << "Reservation " << idR
         << " | Client: " << idC
         << " | Chambre: " << numCh
         << " | Date: " << date << endl;
}

void Reservation::saisir() {
    cout << "ID reservation: ";
    cin >> idR;
    cout << "ID client: ";
    cin >> idC;
    cout << "Numero chambre: ";
    cin >> numCh;
    cout << "Date: ";
    cin >> date;
}

Client clients[MAX_CLIENTS];
Chambre chambres[MAX_CHAMBRES];
Reservation reservations[MAX_RESERVATIONS];

int totC = 0;
int totCh = 0;
int totR = 0;

// Ici on fait la sauvegarde
void ecrireClients() {
    ofstream f("clients.txt");
    for (int i = 0; i < totC; i++)
        f << clients[i].getId() << " " << clients[i].getNom() << " " << clients[i].getContact() << "\n";
}

void lireClients() {
    ifstream f("clients.txt");
    int id; string nom, contact;
    while (f >> id >> nom >> contact) {
        clients[totC] = Client(id, nom, contact);
        totC++;
    }
}

void ecrireChambres() {
    ofstream f("chambres.txt");
    for (int i = 0; i < totCh; i++)
        f << chambres[i].getNumero() << " " << chambres[i].getType() << " "
          << chambres[i].getPrix() << " " << (chambres[i].estDispo() ? 1 : 0) << "\n";
}

void lireChambres() {
    ifstream f("chambres.txt");
    int n, d; string t; double p;
    while (f >> n >> t >> p >> d) {
        chambres[totCh] = Chambre(n, t, p, d == 1);
        totCh++;
    }
}

void ecrireR() {
    ofstream f("reservations.txt");
    for (int i = 0; i < totR; i++)
        f << reservations[i].getIdR() << " "
          << reservations[i].getIdC() << " "
          << reservations[i].getNumCh() << " "
          << reservations[i].getDate() << "\n";
}

void lireR() {
    ifstream f("reservations.txt");
    int r, c, n; string d;
    while (f >> r >> c >> n >> d) {
        reservations[totR] = Reservation(r, c, n, d);
        totR++;
        for (int j = 0; j < totCh; j++)
            if (chambres[j].getNumero() == n) chambres[j].setDispo(false);
    }
}

int rechClient(int id) {
    for (int i = 0; i < totC; i++)
        if (clients[i].getId() == id) return i;
    return -1;
}

int rechChambre(int n) {
    for (int i = 0; i < totCh; i++)
        if (chambres[i].getNumero() == n) return i;
    return -1;
}

int rechRes(int idR) {
    for (int i = 0; i < totR; i++)
        if (reservations[i].getIdR() == idR) return i;
    return -1;
}

// Ajouter / Afficher
void ajoutClient() {
    Client c;
    c.saisir();
    if (rechClient(c.getId()) != -1) {
        cout << "Cet ID existe deja.\n";
        return;
    }
    clients[totC] = c;
    totC++;
    ecrireClients();
    cout << "Client ajoute.\n";
}

void affClients() {
    if (totC == 0) cout << "Aucun client.\n";
    else
        for (int i = 0; i < totC; i++)
            clients[i].afficher();
}

void ajoutCh() {
    Chambre c;
    c.saisir();
    if (rechChambre(c.getNumero()) != -1) {
        cout << "Chambre existe deja.\n";
        return;
    }
    chambres[totCh] = c;
    totCh++;
    ecrireChambres();
    cout << "Chambre ajoutee.\n";
}

void affCh() {
    if (totCh == 0) cout << "Aucune chambre.\n";
    else
        for (int i = 0; i < totCh; i++)
            chambres[i].afficher();
}

// Recherche des chambres libres
void chLibres() {
    cout << "Chambres libres :\n";
    int ok = 0;

    for (int i = 0; i < totCh; i++) {
        if (chambres[i].estDispo()) {
            chambres[i].afficher();
            ok = 1;
        }
    }

    if (!ok) cout << "Aucune chambre libre.\n";
}

void ajoutRes() {
    Reservation r;
    r.saisir();

    if (rechClient(r.getIdC()) == -1) {
        cout << "Client introuvable.\n";
        return;
    }
    int x = rechChambre(r.getNumCh());
    if (x == -1 || !chambres[x].estDispo()) {
        cout << "Chambre non disponible.\n";
        return;
    }

    chambres[x].setDispo(false);
    reservations[totR] = r;
    totR++;

    ecrireR();
    ecrireChambres();
    cout << "Reservation faite.\n";
}

void affRes() {
    if (totR == 0) cout << "Aucune reservation.\n";
    else
        for (int i = 0; i < totR; i++)
            reservations[i].afficher();
}

// Ici on fait les modification
void modifRes() {
    int id;
    cout << "ID reservation a modifier: ";
    cin >> id;

    int pos = rechRes(id);
    if (pos == -1) {
        cout << "Introuvable.\n";
        return;
    }

    cout << "Nouvelle date: ";
    string d;
    cin >> d;
    reservations[pos] = Reservation(id,
                                    reservations[pos].getIdC(),
                                    reservations[pos].getNumCh(),
                                    d);

    ecrireR();
    cout << "Modification terminee.\n";
}

// Ici la suppression
void supRes() {
    int id;
    cout << "ID reservation a supprimer: ";
    cin >> id;

    int pos = rechRes(id);
    if (pos == -1) {
        cout << "Introuvable.\n";
        return;
    }

    int numCh = reservations[pos].getNumCh();

    for (int i = pos; i < totR - 1; i++)
        reservations[i] = reservations[i + 1];

    totR--;

    int x = rechChambre(numCh);
    if (x != -1) chambres[x].setDispo(true);

    ecrireR();
    ecrireChambres();
    cout << "Reservation supprimee.\n";
}

// Menu de demarrage
void menu() {
    int ch = -1;
    while (ch != 0) {
        cout << "\n1-Ajout client\n2-Afficher clients\n3-Ajout chambre\n4-Afficher chambres\n5-Ajout reservation\n6-Afficher reservations\n7-Modifier reservation\n8-Supprimer reservation\n9-Chambres libres\n0-Quitter\nChoix: ";
        cin >> ch;

        if (ch == 1) ajoutClient();
        else if (ch == 2) affClients();
        else if (ch == 3) ajoutCh();
        else if (ch == 4) affCh();
        else if (ch == 5) ajoutRes();
        else if (ch == 6) affRes();
        else if (ch == 7) modifRes();
        else if (ch == 8) supRes();
        else if (ch == 9) chLibres();
        else if (ch == 0) {
            ecrireClients();
            ecrireChambres();
            ecrireR();
            cout << "Bye.\n";
        }
        else cout << "Erreur.\n";
    }
}

int main() {
    lireClients();
    lireChambres();
    lireR();

    cout << "Bienvenue.\n";

    menu();
    return 0;
}
