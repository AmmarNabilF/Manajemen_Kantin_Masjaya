#include <iostream>
#include <windows.h>
#include <thread>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>
#include <ctime>
#include <math.h>
#include <climits>

using namespace std;

struct dataMenu {
    int kodeMenu;
    string namaMenu;
    int harga;
    dataMenu* next;
};

struct pesanan {
    int idPesanan;
    string usernamePembeli;
    int kodeMenu;
    string namaMenu;
    int jumlah;
    string status;
    pesanan* next;
};

struct histori {
    int idPesanan;
    string namaPenjual;
    int kodeMenu;
    string namaMenu;
    int jumlah;
    int harga;
    int sudahDibayar;
    string status;
    histori* next;
};

struct struk {
    int idPesanan;
    string namaPenjual;
    int kodeMenu;
    string namaMenu;
    int jumlah;
    int harga;
    int sudahDibayar;
    string status;
    struk* next;
};

struct dataUser {
    string username;
    string password;
    string role;
    string nama;
    dataMenu* headMenu;
    dataUser* next;
    pesanan* queuePesananHead = nullptr;
    pesanan* queuePesananTail = nullptr;
    histori* stackHistori = nullptr;
    struk* stackStruk = nullptr;
};

dataUser* headUser = nullptr;
int kodeUnikCounter = 999;
int idunikCounter = 0;

bool isUserDataComplete(dataUser* user) {
    return !user->nama.empty();
}

int generateKodeMenu() {
    kodeUnikCounter++;
    return kodeUnikCounter;
}
int generateIdPesanan() {
    idunikCounter++;
    return idunikCounter;
}

void registrasi(){
    system("cls");
    string user, pass, nama;
    cout << "===============================" << endl;
    cout << "      SILAHKAN REGISTRASI" << endl;
    cout << "-------------------------------" << endl;
    cout << "[1] Register Sebagai Penjual" << endl;
    cout << "[2] Register Sebagai Pembeli" << endl;
    cout << "===============================" << endl;
    cout << "Masukkan pilihan: ";
    int pilih;
    cin >> pilih;
    system("cls");
    if (pilih == 1){
        cout << "===============================" << endl;
        cout << "      REGISTRASI PENJUAL" << endl;
        cout << "-------------------------------" << endl;
        cout << "Username: ";
        cin >> user;
        dataUser* data = headUser;
        while (data) {
            if (data->username == user) {
                cout << "Username Telah Dipakai Akun Lain" << endl;
                Sleep(500);
                // Clear the stackHistori when the order is canceled
                return;
            }
            data = data->next;
        }
        cin.ignore();
        cout << "Nama Stand: ";
        getline(cin, nama);
        data = headUser; 
        while (data) {
            if (data->nama == nama) {
                cout << "Nama Stand Sudah Terdaftar" << endl;
                Sleep(500);
                return;
            }
            data = data->next;
        }
        cout << "Password: ";
        cin >> pass;
        dataUser* newUser = new dataUser{user, pass, "Penjual", nama, nullptr, nullptr, nullptr, nullptr};
        if (!headUser) {
            headUser = newUser;
        } else {
            data = headUser;
            while (data->next) {
                data = data->next;
            }
            data->next = newUser;
        }
        system("cls");
        cout << "REGISTRASI BERHASIL!" << endl;
        Sleep(500);
    } else if (pilih == 2){
        cout << "===============================" << endl;
        cout << "      REGISTRASI PEMBELI" << endl;
        cout << "-------------------------------" << endl;
        cout << "Username: ";
        cin >> user;
        dataUser* data = headUser;
        while (data) {
            if (data->username == user) {
                cout << "Username Telah Dipakai Akun Lain" << endl;
                Sleep(500);
                return;
            }
            data = data->next;
        }
        cout << "Password: ";
        cin >> pass;
        dataUser* newUser = new dataUser{user, pass, "Pembeli", "", nullptr, nullptr, nullptr, nullptr};
        if (!headUser) {
            headUser = newUser;
        } else {
            data = headUser;
            while (data->next) {
                data = data->next;
            }
            data->next = newUser;
        }
        system("cls");
        cout << "REGISTRASI BERHASIL!" << endl;
        Sleep(500);
    } else {
        cout << "Pilihan tidak valid" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        Sleep(500);
    }
}

dataUser* menuLogin(int kesempatan = 3) {
    if (kesempatan == 0) {
        cout << "Anda Telah Gagal Login Sebanyak 3 kali. Program berakhir." << endl;
        exit(0);
    }

    system("cls");
    string user, pass;
    cout << "===============================" << endl;
    cout << "        SILAHKAN LOGIN" << endl;
    cout << "------------------------------" << endl;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    cout << "===============================" << endl;
    dataUser* data = headUser;
    while (data) {
        if (data->username == user && data->password == pass) {
            system("cls");
            cout << "LOGIN BERHASIL!" << endl;
            Sleep(500);
            return data;
        }
        data = data->next;
    }
    system("cls");
    cout << "LOGIN GAGAL!" << endl;
    Sleep(500);
    return menuLogin(kesempatan - 1);
}

// ======================== SORT DAN SEARCH ========================

int length(dataMenu* head) {
    int count = 0;
    dataMenu* temp = head;
    while (temp != nullptr) {
        temp = temp->next;
        count++;
    }
    return count;
}

void splitMenuList(dataMenu* source, dataMenu** frontRef, dataMenu** backRef) {
    dataMenu* fast;
    dataMenu* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

dataMenu* mergeSortedMenu(dataMenu* a, dataMenu* b, bool kode) {
    dataMenu* result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (kode) {
        if (a->kodeMenu <= b->kodeMenu) {
            result = a;
            result->next = mergeSortedMenu(a->next, b, kode);
        } else {
            result = b;
            result->next = mergeSortedMenu(a, b->next, kode);
        }
    } else {
        if (a->harga <= b->harga) {
            result = a;
            result->next = mergeSortedMenu(a->next, b, kode);
        } else {
            result = b;
            result->next = mergeSortedMenu(a, b->next, kode);
        }
    }

    return result;
}

void mergeSort(dataMenu** headRef, bool kode) {
    if (*headRef == nullptr || (*headRef)->next == nullptr)
        return;

    dataMenu* head = *headRef;
    dataMenu* a;
    dataMenu* b;

    splitMenuList(head, &a, &b);

    mergeSort(&a, kode);
    mergeSort(&b, kode);

    *headRef = mergeSortedMenu(a, b, kode);
}

dataMenu* partition(dataMenu* low, dataMenu* high, dataMenu** newLow, dataMenu** newHigh) {
    int pivot = high->harga;
    dataMenu* prev = nullptr;
    dataMenu* curr = low;
    dataMenu* tail = high;

    while (curr != high) {
        if (curr->harga > pivot) {
            if ((*newLow) == nullptr) {
                (*newLow) = curr;
            }
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) {
                prev->next = curr->next;
            }
            dataMenu* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if ((*newLow) == nullptr) {
        (*newLow) = high;
    }

    (*newHigh) = tail;

    return high;
}

dataMenu* getTail(dataMenu* curr) {
    while (curr != nullptr && curr->next != nullptr) {
        curr = curr->next;
    }
    return curr;
}

dataMenu* quickSortRecur(dataMenu* low, dataMenu* high) {
    if (!low || low == high) {
        return low;
    }

    dataMenu* newLow = nullptr;
    dataMenu* newHigh = nullptr;

    dataMenu* pivot = partition(low, high, &newLow, &newHigh);

    if (newLow != pivot) {
        dataMenu* temp = newLow;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;

        newLow = quickSortRecur(newLow, temp);

        temp = getTail(newLow);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newHigh);

    return newLow;
}

void quickSort(dataMenu** headRef) {
    if (*headRef == nullptr || (*headRef)->next == nullptr)
        return;
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
}

int fibonacciSearch(dataMenu *head, int x, int n) {
    dataMenu *temp = head;
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);
 
        temp = head;
        for (int j = 0; j < i; j++)
        {
            temp = temp->next;
        }
        if (temp->kodeMenu < x)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (temp->kodeMenu > x)
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
            return i;
    }
    temp = head;
    for (int j = 0; j < offset + 1; j++)
    {
        temp = temp->next;
    }
    if (fibMMm1 && temp->kodeMenu == x)
        return offset + 1;
    return -1;
}

int findNode(dataMenu* head, int idx) {
    for (int i = 0; i < idx; i++) {
        head = head->next;
    }
    return head->kodeMenu;
}

int jumpSearch(dataMenu* head, int x, int n) {
    int step = sqrt(n);
    int prev = 0;
    int idx = min(step, n) - 1;
    while (findNode(head, idx) < x) {
        prev = step;
        step += sqrt(n);
        idx = min(step, n) - 1;
        if (prev >= n) {
            return -1;
        }
    }
    while (findNode(head, prev) < x) {
        prev++;
    }
    if (findNode(head, prev) == x) {
        return prev;
    }
    return -1;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void badCharHeuristic(string str, int size, int badchar[256]) {
    for (int i = 0; i < 256; i++) {
        badchar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badchar[(int)str[i]] = i;
    }
}

dataMenu* boyerMooreSearch(dataMenu* head, string pattern) {
    int badChar[256];
    badCharHeuristic(pattern, pattern.size(), badChar);
    dataMenu* current = head;
    while (current) {
        string text = current->namaMenu;
        int m = pattern.size();
        int n = text.size();
        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && pattern[j] == text[s + j]) {
                j--;
            }
            if (j < 0) {
                return current;
            } else {
                s += max(1, j - badChar[(int)text[s + j]]);
            }
        }
        current = current->next;
    }
    return nullptr;
}

void mergeSortMenu_kode() {
    dataUser* user = headUser;
    while (user) {
        mergeSort(&(user->headMenu), true);
        user = user->next;
    }
}

void mergeSortMenu() {
    dataUser* user = headUser;
    while (user) {
        mergeSort(&(user->headMenu), false);
        user = user->next;
    }
}

void quickSortMenu() {
    dataUser* user = headUser;
    while (user) {
        quickSort(&(user->headMenu));
        user = user->next;
    }
}

void fibonacciSearchMenu(dataUser* currentUser) {
    if (!currentUser->headMenu) {
        cout << "Tidak ada menu yang terdaftar." << endl;
        return;
    }

    mergeSort(&(currentUser->headMenu), true);
    int kodeMenu;
    cout << "\n[SEARCH] Fibonacci Search\n";
    cout << "Masukkan kode menu yang dicari: ";
    cin >> kodeMenu;
    int index = fibonacciSearch(currentUser->headMenu, kodeMenu, length(currentUser->headMenu));

    cout << "\nHasil pencarian untuk '" << kodeMenu << "':\n";
    cout << "----------------------------------------------\n";
    if (index != -1) {
        dataMenu* foundMenu = currentUser->headMenu;
        for (int i = 0; i < index; i++) {
            foundMenu = foundMenu->next;
        }
        cout << "Menu ditemukan!\n"
             << "Kode menu: " << foundMenu->kodeMenu << "\n"
             << "Nama menu: " << foundMenu->namaMenu << "\n"
             << "Harga: Rp" << foundMenu->harga << "\n"
             << "----------------------------------------------\n";
    } else {
        cout << "Menu tidak ditemukan.\n" << endl;
    }
}

void jumpSearchMenu(dataUser* currentUser) {
    if (!currentUser->headMenu) {
        cout << "Tidak ada menu yang terdaftar." << endl;
        return;
    }

    mergeSort(&(currentUser->headMenu), true);
    int kodeMenu;
    cout << "\n[SEARCH] Jump Search\n";
    cout << "Masukkan kode menu yang dicari: ";
    cin >> kodeMenu;
    int index = jumpSearch(currentUser->headMenu, kodeMenu, length(currentUser->headMenu));

    cout << "\nHasil pencarian untuk '" << kodeMenu << "':\n";
    cout << "----------------------------------------------\n";
    if (index != -1) {
        dataMenu* foundMenu = currentUser->headMenu;
        for (int i = 0; i < index; i++) {
            foundMenu = foundMenu->next;
        }
        cout << "Menu ditemukan!\n"
             << "Kode menu: " << foundMenu->kodeMenu << "\n"
             << "Nama menu: " << foundMenu->namaMenu << "\n"
             << "Harga: Rp" << foundMenu->harga << "\n"
             << "----------------------------------------------\n";
    } else {
        cout << "Menu tidak ditemukan.\n" << endl;
    }
}

void boyerMooreSearchMenu(dataUser* currentUser) {
    string namaMenu;
    cout << "\n[SEARCH] Boyer-Moore Search\n";
    cout << "Masukkan nama menu yang dicari: ";
    getline(cin, namaMenu);
    quickSort(&(currentUser->headMenu));
    dataMenu* result = boyerMooreSearch(currentUser->headMenu, namaMenu);
    cout << "\nHasil pencarian untuk '" << namaMenu << "':\n";
    cout << "----------------------------------------------\n";
    bool found = false;
    while (result) {
        cout << "Menu ditemukan!" << endl 
             << "Kode menu: " << result->kodeMenu << endl
             << "Nama menu: " << result->namaMenu << endl
             << "Harga    : Rp" << result->harga << endl
             << "----------------------------------------------\n";
        found = true;
        result = boyerMooreSearch(result->next, namaMenu);
    }
    if (!found) {
        cout << "Menu tidak ditemukan.\n" << endl;
    }
}

int inputHarga() {
    int harga;
    while (true) {
        cout << "Masukkan harga untuk menu: Rp";
        cin >> harga;
        if (!cin.fail() && harga > 0) {
            break;
        } else {
            cout << "Input tidak valid\nMasukkan harga dalam angka positif\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }
    return harga;
}

void addMenu(dataUser* user) {
    system("cls");
    string namaMenu;
    cin.clear();
    cin.ignore();
    cout << "\nNama Menu: ";
    getline(cin, namaMenu);

    int harga = inputHarga();
    int kodeMenu = generateKodeMenu();

    dataMenu* newMenu = new dataMenu{kodeMenu, namaMenu, harga, nullptr};

    newMenu->next = user->headMenu;
    user->headMenu = newMenu;

    cout << "Menu berhasil ditambahkan di awal." << endl;
}

void delMenuAwal(dataUser* user) {
    system("cls");

    if (!user->headMenu) {
        cout << "Anda belum memiliki menu yang terdaftar." << endl;
        return;
    }

    dataMenu* temp = user->headMenu;
    user->headMenu = user->headMenu->next;
    delete temp;

    cout << "Menu di awal berhasil dihapus." << endl;
}

void delMenu(dataUser* user) {
    system("cls");
    
    dataMenu* data = user->headMenu;
    if (!data) {
        cout << "Anda belum memiliki menu yang terdaftar." << endl;
        return;
    } else {
        cout << "\nMenu yang terdaftar:\n";
        while (data) {
            cout << "- Kode Menu: " << data->kodeMenu << ", Nama Menu: " << data->namaMenu << ", Harga: Rp" << data->harga << endl;
            data = data->next;
        }
    }

    int kode;
    cout << "Masukkan kode menu yang ingin dihapus: ";
    cin >> kode;

    dataMenu* curr = user->headMenu;
    dataMenu* prev = nullptr;

    while (curr) {
        if (curr->kodeMenu == kode) {
            if (prev) {
                prev->next = curr->next;
            } else {
                user->headMenu = curr->next;
            }
            delete curr;
            cout << "Menu dengan kode " << kode << " berhasil dihapus." << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Menu dengan kode " << kode << " tidak ditemukan." << endl;
}

void buyMenu(dataUser* pembeli, dataMenu* menu, dataUser* penjual, int jumlah) {
    int totalHarga = menu->harga * jumlah;

    int idUnikPesanan = generateIdPesanan();
    
    pesanan* newPesanan = new pesanan{idUnikPesanan, pembeli->username, menu->kodeMenu, menu->namaMenu, jumlah ,"Pending", nullptr};
    if (!penjual->queuePesananTail) {
        penjual->queuePesananHead = penjual->queuePesananTail = newPesanan;
    } else {
        penjual->queuePesananTail->next = newPesanan;
        penjual->queuePesananTail = newPesanan;
    }

    struk* newStrukItem = new struk{idUnikPesanan, penjual->nama, menu->kodeMenu, menu->namaMenu, jumlah, menu->harga, 0, "Pending", pembeli->stackStruk};
    pembeli->stackStruk = newStrukItem;

    cout << "Pesanan berhasil ditambahkan ke keranjang!" << endl;
    Sleep(500);
}

void checkout(dataUser* pembeli) {
    system("cls");
    int totalHarga = 0;
    struk* currentItem = pembeli->stackStruk;
    int idPesanan = 0;

    if (!currentItem) {
        cout << "Keranjang belanja kosong." << endl;
        return;
    }

    cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(16) << "=" << setfill(' ') << "      DAFTAR PESANAN      " << setfill('=') << setw(18) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    cout << left << setw(20) << "Nama Menu" 
        << setw(10) << "Jumlah" 
        << setw(15) << "Harga" 
        << setw(15) << "Total" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    while (currentItem) {
        if (idPesanan == 0) {
            idPesanan = currentItem->idPesanan;
        }
        totalHarga += currentItem->jumlah * currentItem->harga;
        cout << left << setw(20) << currentItem->namaMenu 
            << setw(10) << currentItem->jumlah 
            << setw(15) << "Rp" + to_string(currentItem->harga) 
            << setw(15) << "Rp" + to_string(currentItem->jumlah * currentItem->harga) << endl;
        currentItem = currentItem->next;
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    }
    cout << "Total Harga: Rp" << totalHarga << endl;
    cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;

    int pilihan;
    cout << "\n===============================" << endl;
    cout << "              AKSI             " << endl;
    cout << "===============================" << endl;
    cout << "[1] Batalkan Pesanan" << endl;
    cout << "[2] Lanjut Pembayaran" << endl;
    cout << "===============================" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    if (pilihan == 1) {
        // Hapus semua pesanan dari struk
        while (pembeli->stackStruk) {
            struk* temp = pembeli->stackStruk;
            pembeli->stackStruk = pembeli->stackStruk->next;
            delete temp;
        }
        system("cls");
        cout << "Pesanan dibatalkan." << endl << endl;
        return;
    } else if (pilihan == 2) {
        currentItem = pembeli->stackStruk;
        while (currentItem) {
            histori* newHistoriItem = new histori{
                currentItem->idPesanan, currentItem->namaPenjual, currentItem->kodeMenu, 
                currentItem->namaMenu, currentItem->jumlah, currentItem->harga, 1, "Pending", pembeli->stackHistori
            };
            pembeli->stackHistori = newHistoriItem;
            currentItem = currentItem->next;
        }
        while (pembeli->stackStruk) {
            struk* temp = pembeli->stackStruk;
            pembeli->stackStruk = pembeli->stackStruk->next;
            delete temp;
        }
        system("cls");
        cout << "Pesanan berhasil! Silakan bayar pesanan ke kasir." << endl << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}

void showMenuPenjual(dataUser* user) {
    system("cls");
    cout << "\n" << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(17) << "=" << setfill(' ') << "      DAFTAR  MENU      " << setfill('=') << setw(19) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    cout << left << setw(20) << "Kode Menu" << setw(30) << "Nama Menu" << setw(11) << "Harga" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

    dataMenu* menu = user->headMenu;
    while (menu) {
        cout << left << setw(20) << menu->kodeMenu
             << setw(30) << menu->namaMenu
             << "Rp" << menu->harga << endl;
        menu = menu->next;
    }
    cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
}


void beli(dataUser* currentUser, dataUser* headUser) {
    dataUser* user = headUser;
    int index = 1;

    cout << "\n" << setfill('=') << setw(47) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(10) << "=" << setfill(' ') << "      DAFTAR STAND      " << setfill('=') << setw(13) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(47) << "=" << setfill(' ') << endl;
    cout << left << setw(5) << "No" << setw(20) << "Nama Stand" << endl;
    cout << setfill('-') << setw(47) << "-" << setfill(' ') << endl;

    while (user) {
        if (user->role == "Penjual") {
            cout << left << setw(5) << index << setw(20) << user->nama << endl;
            index++;
        }
        user = user->next;
    }
    cout << setfill('=') << setw(47) << "=" << setfill(' ') << endl;

    int pilihan;
    cout << "Masukkan nomor stand yang ingin dilihat: ";
    cin >> pilihan;
    cin.ignore();

    user = headUser;
    index = 1;
    while (user) {
        if (user->role == "Penjual") {
            if (index == pilihan) {
                while (true) {
                    system("cls");
                    showMenuPenjual(user);
                    int kodeMenu;
                    int jumlah;
                    cout << "Masukkan kode menu yang ingin dibeli (atau 0 untuk checkout): ";
                    cin >> kodeMenu;
                    cin.ignore();
                    
                    if (kodeMenu == 0) {
                        checkout(currentUser);
                        break;
                    }

                    cout << "Masukkan jumlah yang ingin dibeli: ";
                    cin >> jumlah;
                    cin.ignore();

                    dataUser* penjual = headUser;
                    dataMenu* menu = nullptr;
                    menu = user->headMenu;
                    while (menu) {
                        if (menu->kodeMenu == kodeMenu) {
                            break;
                        }
                        menu = menu->next;
                    }

                    if (menu) {
                        buyMenu(currentUser, menu, user, jumlah);
                    } else {
                        cout << "Menu dengan kode " << kodeMenu << " tidak ditemukan." << endl;
                    }
                }
                return;
            }
            index++;
        }
        user = user->next;
    }
    cout << "Stand dengan nomor " << pilihan << " tidak ditemukan." << endl;
}

void showPesanan(dataUser* user) {
    system("cls"); 
    pesanan* curr = user->queuePesananHead;
    pesanan* prev = nullptr;

    if (!curr) {
        cout << "Tidak ada pesanan saat ini" << endl;
        Sleep(1000);
        return;
    }

    while (curr) {
        cout << "======================================" << endl;
        cout << "|           ID PESANAN: " << setw(2) << curr->idPesanan << "           |" << endl;
        cout << "======================================" << endl;
        cout << left << setw(12) << "Pembeli"   << ": " << curr->usernamePembeli << endl;
        cout << left << setw(12) << "Nama Menu" << ": " << curr->namaMenu << endl;
        cout << left << setw(12) << "Jumlah"    << ": " << curr->jumlah << endl;
        cout << left << setw(12) << "Status"    << ": " << curr->status << endl;
        cout << "======================================" << endl;

        int pilihan;
        cout << "\n===============================" << endl;
        cout << "              AKSI             " << endl;
        cout << "===============================" << endl;
        cout << "[1] Tandai selesai pesanan" << endl;
        cout << "[2] Batalkan pesanan" << endl;
        cout << "[0] Kembali" << endl;
        cout << "===============================" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            curr->status = "Complete";
            cout << "Pesanan ditandai selesai!" << endl;
        } else if (pilihan == 2) {
            curr->status = "Cancel";
            cout << "Pesanan ditolak!" << endl;
        } else if (pilihan == 0) {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
            continue;
        }
        Sleep(1000);
        system("cls");
        dataUser* userIter = headUser;
        while (userIter) {
            histori* hist = userIter->stackHistori;
            while (hist) {
                if (hist->idPesanan == curr->idPesanan) {
                    hist->status = curr->status;
                    hist->sudahDibayar = (pilihan == 1) ? 1 : 2;
                }
                hist = hist->next;
            }
            userIter = userIter->next;
        }

        if (prev) {
            prev->next = curr->next;
        } else {
            user->queuePesananHead = curr->next;
        }
        if (curr == user->queuePesananTail) {
            user->queuePesananTail = prev;
        }
        pesanan* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void showHistory(dataUser* user) {
    system("cls");

    histori* curr = user->stackHistori;

    if (!curr) {
        cout << "Tidak ada histori pembelian" << endl;
        return;
    }

    cout << "RIWAYAT PEMESANAN" << endl << endl;
    cout << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    cout << left << setw(10) << "ID"
         << setw(18) << "Nama Stand" 
         << setw(16) << "Kode Menu" 
         << setw(20) << "Nama Menu" 
         << setw(15) << "Jumlah" 
         << setw(15) << "Harga Satuan" 
         << setw(15) << "Total Harga"
         << setw(15) << "Status" << endl;

    int totalHarga = 0;
    while (curr) {
        int hargaTotalItem = curr->jumlah * curr->harga; 
        cout << setfill('-') << setw(120) << "=" << setfill(' ') << endl;
        cout << left << setw(10) << curr->idPesanan
             << setw(18) << curr->namaPenjual
             << setw(16) << curr->kodeMenu
             << setw(20) << curr->namaMenu
             << setw(15) << curr->jumlah << "Rp"
             << setw(13) << curr->harga << "Rp"
             << setw(13) << hargaTotalItem
             << curr->status << endl;
        totalHarga += hargaTotalItem;

        curr = curr->next;
    }
    cout << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
}

void ubahmenu(dataUser* user) {
    system("cls");
    dataMenu* data = user->headMenu;
    if (!data) {
        cout << "Anda belum memiliki menu yang terdaftar." << endl;
        return;
    } else {
        cout << "\nMenu yang terdaftar:\n";
        while (data) {
            cout << "- Kode Menu: " << data->kodeMenu << ", Nama Menu: " << data->namaMenu << ", Harga: Rp" << data->harga << endl;
            data = data->next;
        }
    }

    int kode;
    cout << "Masukkan kode menu yang ingin diubah: ";
    cin >> kode;

    dataMenu* curr = user->headMenu;
    while (curr) {
        if (curr->kodeMenu == kode) {
            cout << "Masukkan Nama Menu: ";
            cin.clear();
            cin.ignore();
            getline(cin, curr->namaMenu);
            curr->harga = inputHarga();
            cout << "Menu berhasil diubah." << endl;
            return;
        }
        curr = curr->next;
    }

    cout << "Menu dengan kode " << kode << " tidak ditemukan." << endl;
}

void sort(dataUser* currentUser) {
    while (true) {
        system("cls");
        showMenuPenjual(currentUser);
        int pilihan;
        cout << "\n===============================\n";
        cout << "|         MENU SORTING        |\n";
        cout << "===============================\n";
        cout << "| Pilih metode pengurutan:    |\n";
        cout << "| [1] Merge Sort (Ascending)  |\n";
        cout << "| [2] Quick Sort (Descending) |\n";
        cout << "| [0] Kembali                 |\n";
        cout << "===============================\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            mergeSortMenu();
            cout << "Menu berhasil diurutkan secara ascending berdasarkan harga." << endl;
            Sleep(500);
        } else if (pilihan == 2) {
            quickSortMenu();
            cout << "Menu berhasil diurutkan secara descending berdasarkan harga." << endl;
            Sleep(500);
        } else if (pilihan == 0) {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
            Sleep(500);
        }
    }
}

void searchPenjual(dataUser* currentUser) {
    while (true) {
        system("cls");
        showMenuPenjual(currentUser);
        int pilihan;
        cout << "\n===============================\n";
        cout << "|         MENU SEARCHING      |\n";
        cout << "===============================\n";
        cout << "|Pilih metode pencarian:      |\n";
        cout << "|[1] Fibonacci Search (kode)  |\n";
        cout << "|[2] Jump Search (kode)       |\n";
        cout << "|[3] Boyer-Moore Search (nama)|\n";
        cout << "|[0] Kembali                  |\n";
        cout << "===============================\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            fibonacciSearchMenu(currentUser);
            system("pause");
        } else if (pilihan == 2) {
            jumpSearchMenu(currentUser);
            system("pause");
        } else if (pilihan == 3) {
            boyerMooreSearchMenu(currentUser);
            system("pause");
        } else if (pilihan == 0) {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}

void search(dataUser* currentUser) {
    int pilihan;
    cout << "\n===============================\n";
    cout << "|         MENU SEARCHING      |\n";
    cout << "===============================\n";
    cout << "Cari berdasarkan nama menu\n\n";

    boyerMooreSearchMenu(currentUser);
    system("pause");
}

void pilihMenu() {
    system("cls");
    dataUser* user = headUser;
    int index = 1;

    cout << "\n" << setfill('=') << setw(47) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(10) << "=" << setfill(' ') << "      DAFTAR STAND      " << setfill('=') << setw(13) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(47) << "=" << setfill(' ') << endl;
    cout << left << setw(5) << "No" << setw(20) << "Nama Stand" << endl;
    cout << setfill('-') << setw(47) << "-" << setfill(' ') << endl;

    while (user) {
        if (user->role == "Penjual") {
            cout << left << setw(5) << index << setw(20) << user->nama << endl;
            index++;
        }
        user = user->next;
    }
    cout << setfill('=') << setw(47) << "=" << setfill(' ') << endl;

    int pilihan;
    cout << "Masukkan nomor stand yang ingin dilihat: ";
    cin >> pilihan;
    cin.ignore();

    user = headUser;
    index = 1;
    while (user) {
        if (user->role == "Penjual") {
            if (index == pilihan) {
                showMenuPenjual(user);
                return;
            }
            index++;
        }
        user = user->next;
    }
    cout << "Stand dengan nomor " << pilihan << " tidak ditemukan." << endl;
}

int main() {
dataUser* penjual1 = new dataUser{"p1", "p1", "Penjual", "Stand Penjual 1", nullptr, nullptr, nullptr, nullptr};
dataUser* penjual2 = new dataUser{"p2", "p2", "Penjual", "Stand Penjual 2", nullptr, nullptr, nullptr, nullptr};

dataMenu* menu1 = new dataMenu{9000, "Nasi Goreng", 15000, nullptr};
dataMenu* menu2 = new dataMenu{9001, "Mie Goreng", 12000, nullptr};
dataMenu* menu3 = new dataMenu{9002, "Ayam Bakar", 20000, nullptr};
dataMenu* menu4 = new dataMenu{9003, "Sate Ayam", 18000, nullptr};

penjual1->headMenu = menu1;
menu1->next = menu2;

penjual2->headMenu = menu3;
menu3->next = menu4;

headUser = penjual1;
penjual1->next = penjual2;

int pilihan;
dataUser* currentUser = nullptr;
    while (true) {
        system("cls");
        cout << "=======================================" << endl;
        cout << "   Selamat Datang di Kantin Masjaya" << endl;
        cout << "---------------------------------------" << endl;
        cout << "[1] Registrasi" << endl;
        cout << "[2] Login" << endl;
        cout << "[3] Keluar" << endl;
        cout << "=======================================" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                registrasi();
                break;
            case 2:
                currentUser = menuLogin();
                if (currentUser->role == "Penjual") {
                    int subPilihanPenjual;
                    do {
                        system("cls");
                        cout << "=======================================" << endl;
                        cout << "             MENU PENJUAL" << endl;
                        cout << "---------------------------------------" << endl;
                        cout << "   Selamat Datang, " << currentUser->nama << endl;
                        cout << "---------------------------------------" << endl;
                        cout << "[1] Lihat Menu Anda" << endl;
                        cout << "[2] Tambah Menu" << endl;
                        cout << "[3] Ubah Menu" << endl;
                        cout << "[4] Hapus Menu Di Awal" << endl;
                        cout << "[5] Hapus Menu Berdasarkan Kode" << endl;
                        cout << "[6] Lihat Pesanan" << endl;
                        cout << "[7] Logout" << endl;
                        cout << "=======================================" << endl;
                        cout << "Masukkan pilihan: ";
                        cin >> subPilihanPenjual;
                        switch (subPilihanPenjual) {
                            case 1:
                                while (true){
                                    showMenuPenjual(currentUser);
                                    int pilihan;
                                    cout << "\n==================" << endl;
                                    cout << "[1] Urutkan Menu" << endl;
                                    cout << "[2] Cari Menu" << endl;
                                    cout << "[0] Kembali" << endl;
                                    cout << "=================" << endl;
                                    cout << "Masukkan pilihan: ";
                                    cin >> pilihan;
                                    if (pilihan == 1){
                                        sort(currentUser);
                                    } else if (pilihan == 2){
                                        searchPenjual(currentUser);
                                    } else if (pilihan == 0){
                                        break;
                                    } else {
                                        cout << "Pilihan tidak valid." << endl;
                                        cin.clear();
                                        cin.ignore(INT_MAX, '\n');
                                        Sleep(500);
                                    }
                                }
                                break;
                            case 2:
                                addMenu(currentUser);
                                system("pause");
                                break;
                            case 3:
                                ubahmenu(currentUser);
                                system("pause");
                                break;
                            case 4:
                                delMenuAwal(currentUser);
                                system("pause");
                                break;
                            case 5:
                                delMenu(currentUser);
                                system("pause");
                                break;
                            case 6:
                                showPesanan(currentUser);
                                break;
                            case 7:
                                currentUser = nullptr;
                                break;
                            default:
                                cout << "Pilihan tidak valid." << endl;
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                Sleep(500);
                                break;
                        }
                    } while (subPilihanPenjual != 7);
                } else if (currentUser->role == "Pembeli") {
                    int subPilihanPembeli;
                    do {
                        system("cls");
                        cout << "=======================================" << endl;
                        cout << "             MENU PEMBELI" << endl;
                        cout << "---------------------------------------" << endl;
                        cout << "   Selamat Datang, " << currentUser->username << endl;
                        cout << "---------------------------------------" << endl;
                        cout << "[1] Lihat Menu" << endl;
                        cout << "[2] Pesan" << endl;
                        cout << "[3] Lihat Riwayat Pemesanan" << endl;
                        cout << "[4] Logout" << endl;
                        cout << "=======================================" << endl;
                        cout << "Masukkan pilihan: ";
                        cin >> subPilihanPembeli;
                        switch (subPilihanPembeli) {
                            case 1:
                                while (true) {
                                    pilihMenu();
                                    int pilihan;
                                    cout << "\n==================" << endl;
                                    cout << "[1] Urutkan Menu" << endl;
                                    cout << "[2] Cari Menu" << endl;
                                    cout << "[0] Kembali" << endl;
                                    cout << "=================" << endl;
                                    cout << "Masukkan pilihan: ";
                                    cin >> pilihan;
                                    cin.ignore();
                                    if (pilihan == 1){
                                        sort(currentUser);
                                    } else if (pilihan == 2){
                                        search(currentUser);
                                    } else if (pilihan == 0){
                                        break;
                                    } else {
                                        cout << "Pilihan tidak valid." << endl;
                                        cin.clear();
                                        cin.ignore(INT_MAX, '\n');
                                        Sleep(500);
                                    }
                                }
                                break;
                            case 2:
                                system("cls");
                                beli(currentUser, headUser);
                                system("pause");
                                break;
                            case 3:
                                showHistory(currentUser);
                                system("pause");
                                break;
                            case 4:
                                currentUser = nullptr;
                                break;
                            default:
                                cout << "Pilihan tidak valid." << endl;
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                Sleep(500);
                                break;
                        }
                    } while (subPilihanPembeli != 4);
                }
                break;
            case 3:
                return 0;
            default:
                cout << "Pilihan tidak valid." << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                Sleep(500);
                break;
        }
    }
}