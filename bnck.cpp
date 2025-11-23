#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_ACCOUNTS = 5;

class BankAccount {
private:
    int accno;
    string name;
    string address;
    char actype;
    float amount;

public:
    // Constructeur
    BankAccount() : accno(0), name(""), address(""), actype('\0'), amount(0.0) {}

    // Getters
    int getAccountNumber() const { return accno; }
    bool isEmpty() const {
        return accno == 0 && name == "" && address == "" && actype == '\0' && amount == 0.0;
    }

    // Opérations sur le compte
    void createAccount();
    void deposit();
    void withdraw();
    void displayAccount() const;
    void modifyAccount();
    void deleteAccount();

    // Recherche
    bool matchesAccountNumber(int searchAccno) const {
        return accno == searchAccno;
    }
};

// Fonctions utilitaires
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pressAnyKeyToContinue() {
    cout << "\nAppuyez sur Entrée pour continuer...";
    clearInputBuffer();
    cin.get();
}

BankAccount* findAccount(BankAccount accounts[], int accountNumber) {
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (accounts[i].matchesAccountNumber(accountNumber)) {
            return &accounts[i];
        }
    }
    return nullptr;
}

int findEmptyAccountSlot(BankAccount accounts[]) {
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (accounts[i].isEmpty()) {
            return i;
        }
    }
    return -1;
}

// Implémentation des méthodes de BankAccount
void BankAccount::createAccount() {
    cout << "Numéro de compte : ";
    cin >> accno;
    
    clearInputBuffer();
    
    cout << "Nom complet : ";
    getline(cin, name);
    
    cout << "Adresse : ";
    getline(cin, address);
    
    cout << "Type de compte (s: épargne, c: courant) : ";
    cin >> actype;
    
    cout << "Montant du dépôt initial : ";
    cin >> amount;
    
    cout << "Compte créé avec succès !\n";
}

void BankAccount::deposit() {
    float depositAmount;
    cout << "Montant à déposer : ";
    cin >> depositAmount;
    
    if (depositAmount > 0) {
        amount += depositAmount;
        cout << "Dépôt réussi. Nouveau solde : " << amount << endl;
    } else {
        cout << "Montant invalide !\n";
    }
}

void BankAccount::withdraw() {
    float withdrawAmount;
    cout << "Montant à retirer : ";
    cin >> withdrawAmount;
    
    if (withdrawAmount > 0 && withdrawAmount <= amount) {
        amount -= withdrawAmount;
        cout << "Retrait réussi. Solde restant : " << amount << endl;
    } else if (withdrawAmount > amount) {
        cout << "Fonds insuffisants !\n";
    } else {
        cout << "Montant invalide !\n";
    }
}

void BankAccount::displayAccount() const {
    cout << "\n--- Informations du compte ---\n";
    cout << "Numéro de compte : " << accno << endl;
    cout << "Nom : " << name << endl;
    cout << "Adresse : " << address << endl;
    cout << "Type de compte : " << (actype == 's' ? "Épargne" : "Courant") << endl;
    cout << "Solde : " << amount << endl;
    cout << "--------------------------------\n";
}

void BankAccount::modifyAccount() {
    clearInputBuffer();
    
    cout << "Nouveau nom (" << name << ") : ";
    getline(cin, name);
    
    cout << "Nouvelle adresse (" << address << ") : ";
    getline(cin, address);
    
    cout << "Nouveau type de compte (" << actype << ") : ";
    cin >> actype;
    
    cout << "Compte modifié avec succès !\n";
}

void BankAccount::deleteAccount() {
    accno = 0;
    name = "";
    address = "";
    actype = '\0';
    amount = 0.0;
    cout << "Compte supprimé avec succès !\n";
}

void displayMenu() {
    system("cls"); // Utiliser "clear" sur Linux/Mac
    cout << "==========================================\n";
    cout << "|          SYSTÈME BANCAIRE             |\n";
    cout << "==========================================\n";
    cout << "1. Créer un nouveau compte\n";
    cout << "2. Effectuer un dépôt\n";
    cout << "3. Effectuer un retrait\n";
    cout << "4. Consulter un compte\n";
    cout << "5. Modifier un compte\n";
    cout << "6. Supprimer un compte\n";
    cout << "7. Afficher tous les comptes\n";
    cout << "8. Quitter\n";
    cout << "==========================================\n";
    cout << "Votre choix : ";
}

int main() {
    BankAccount accounts[MAX_ACCOUNTS];
    int choice;
    int accountNumber;
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: { // Créer un compte
                int emptySlot = findEmptyAccountSlot(accounts);
                if (emptySlot != -1) {
                    accounts[emptySlot].createAccount();
                } else {
                    cout << "Nombre maximum de comptes atteint !\n";
                }
                break;
            }
                
            case 2: { // Dépôt
                cout << "Numéro de compte : ";
                cin >> accountNumber;
                
                BankAccount* account = findAccount(accounts, accountNumber);
                if (account != nullptr) {
                    account->deposit();
                } else {
                    cout << "Compte non trouvé !\n";
                }
                break;
            }
                
            case 3: { // Retrait
                cout << "Numéro de compte : ";
                cin >> accountNumber;
                
                BankAccount* account = findAccount(accounts, accountNumber);
                if (account != nullptr) {
                    account->withdraw();
                } else {
                    cout << "Compte non trouvé !\n";
                }
                break;
            }
                
            case 4: { // Consulter
                cout << "Numéro de compte : ";
                cin >> accountNumber;
                
                BankAccount* account = findAccount(accounts, accountNumber);
                if (account != nullptr) {
                    account->displayAccount();
                } else {
                    cout << "Compte non trouvé !\n";
                }
                break;
            }
                
            case 5: { // Modifier
                cout << "Numéro de compte : ";
                cin >> accountNumber;
                
                BankAccount* account = findAccount(accounts, accountNumber);
                if (account != nullptr) {
                    account->modifyAccount();
                } else {
                    cout << "Compte non trouvé !\n";
                }
                break;
            }
                
            case 6: { // Supprimer
                cout << "Numéro de compte : ";
                cin >> accountNumber;
                
                BankAccount* account = findAccount(accounts, accountNumber);
                if (account != nullptr) {
                    account->deleteAccount();
                } else {
                    cout << "Compte non trouvé !\n";
                }
                break;
            }
                
            case 7: { // Afficher tous les comptes
                bool found = false;
                for (int i = 0; i < MAX_ACCOUNTS; i++) {
                    if (!accounts[i].isEmpty()) {
                        accounts[i].displayAccount();
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Aucun compte trouvé !\n";
                }
                break;
            }
                
            case 8: // Quitter
                cout << "Merci d'avoir utilisé notre système bancaire !\n";
                return 0;
                
            default:
                cout << "Choix invalide !\n";
        }
        
        pressAnyKeyToContinue();
    }
    
    return 0;
}