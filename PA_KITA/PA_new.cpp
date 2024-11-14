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
    string kodeMenu;
    string namaMenu;
    int harga;
    dataMenu* next;
};

struct pesanan {
    string idPesanan;
    string usernamePembeli;
    string kodeMenu;
    string status;
    pesanan* next;
};

struct histori {
    string idPesanan;
    string namaPenjual;
    string kodeMenu;
    string namaMenu;
    int jumlah;
    int harga;
    int sudahDibayar;
    string status;
    histori* next;
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
};

dataUser* headUser = nullptr;
int kodeUnikCounter = 1;
int idunikCounter = 1;

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

dataMenu* mergeSortedMenu(dataMenu* a, dataMenu* b) {
    dataMenu* result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (a->harga <= b->harga) {
        result = a;
        result->next = mergeSortedMenu(a->next, b);
    } else {
        result = b;
        result->next = mergeSortedMenu(a, b->next);
    }

    return result;
}

void mergeSortMenu(dataMenu** headRef) {
    if (*headRef == nullptr || (*headRef)->next == nullptr)
        return;

    dataMenu* head = *headRef;
    dataMenu* a;
    dataMenu* b;

    splitMenuList(head, &a, &b);

    mergeSortMenu(&a);
    mergeSortMenu(&b);

    *headRef = mergeSortedMenu(a, b);
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

void quickSortMenu(dataMenu** headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
}

bool isUserDataComplete(dataUser* user) {
    return !user->nama.empty();
}

string generateKodeMenu() {
    stringstream ss;
    ss << "M" << kodeUnikCounter++;
    return ss.str();
}
string generateIdPesanan() {
    stringstream ss;
    ss << "P" << idunikCounter++;
    return ss.str();
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
    string kodeMenu = generateKodeMenu();

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

    string kode;
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

    string idUnikPesanan = generateIdPesanan();
    
    pesanan* newPesanan = new pesanan{idUnikPesanan, pembeli->username, menu->kodeMenu, "Pending", nullptr};
    if (!penjual->queuePesananTail) {
        penjual->queuePesananHead = penjual->queuePesananTail = newPesanan;
    } else {
        penjual->queuePesananTail->next = newPesanan;
        penjual->queuePesananTail = newPesanan;
    }

    histori* newStackItem = new histori{idUnikPesanan, penjual->nama, menu->kodeMenu, menu->namaMenu, jumlah, menu->harga, 0, "Pending", pembeli->stackHistori};
    pembeli->stackHistori = newStackItem;

    cout << "Pesanan berhasil ditambahkan ke keranjang!" << endl;
    Sleep(500);
}


void checkout(dataUser* pembeli) {
    system("cls");
    int totalHarga = 0;
    histori* currentItem = pembeli->stackHistori;
    while (currentItem) {
        totalHarga += currentItem->jumlah * currentItem->harga;
        currentItem = currentItem->next;
    }

    if (totalHarga == 0) {
        cout << "Keranjang belanja kosong." << endl;
        return;
    }

    cout << "Daftar Pesanan:\n";
    currentItem = pembeli->stackHistori;
    while (currentItem) {
        cout << "Nama Menu: " << currentItem->namaMenu 
            << " | Jumlah: " << currentItem->jumlah 
            << " | Harga: Rp" << currentItem->harga 
            << " | Total: Rp" << currentItem->jumlah * currentItem->harga << endl;
        currentItem = currentItem->next;
    }
    cout << "Total Harga: Rp" << totalHarga << endl;

    int pilihan;
    cout << "1. Batalkan Pesanan\n2. Lanjutkan Pembayaran\nPilihan: ";
    cin >> pilihan;

    if (pilihan == 1) {
        cout << "Pesanan dibatalkan." << endl;
        return;
    } else if (pilihan == 2) {
        currentItem = pembeli->stackHistori;
        while (currentItem) {
            currentItem->sudahDibayar = 1;
            currentItem->status = "Pending";
            currentItem = currentItem->next;
        }
        cout << "Pesanan berhasil! Silakan bayar pesanan ke kasir." << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}

void showMenu() {
    system("cls");
    dataUser* user = headUser;
    cout << "\n" << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(27) << "=" << setfill(' ') << "      Daftar Menu      " << setfill('=') << setw(27) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
    cout << left << setw(11) << "Kode Menu" << setw(20) << "Nama Menu" << setw(20) << "Harga" << setw(20) << "Penjual" << endl;
    cout << setfill('=') << setw(81) << "=" << setfill(' ') << endl;

    while (user) {
        dataMenu* menu = user->headMenu;
        while (menu) {
            cout << left << setw(11) << menu->kodeMenu
                 << setw(20) << menu->namaMenu
                 << "Rp" << setw(17) << menu->harga
                 << user->nama << endl;
            menu = menu->next;
        }
        user = user->next;
    }
    cout << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
}

void showMenuPenjual(dataUser* user) {
    system("cls");
    cout << "\n" << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(27) << "=" << setfill(' ') << "      Daftar Menu      " << setfill('=') << setw(27) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
    cout << left << setw(11) << "Kode Menu" << setw(20) << "Nama Menu" << setw(20) << "Harga" << endl;
    cout << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
    
    dataMenu* menu = user->headMenu;
    while (menu) {
        cout << left << setw(11) << menu->kodeMenu
             << setw(20) << menu->namaMenu
             << "Rp" << menu->harga << endl;
        menu = menu->next;
    }
    cout << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
}

void beli(dataUser* currentUser, dataUser* headUser) {
    while (true) {
        showMenu();
        string kodeMenu;
        int jumlah;
        cout << "Masukkan kode menu yang ingin dibeli (atau 0 untuk checkout): ";
        cin >> kodeMenu;
        
        if (kodeMenu == "0") {
            checkout(currentUser);
            break;
        }

        cout << "Masukkan jumlah yang ingin dibeli: ";
        cin >> jumlah;

        dataUser* penjual = headUser;
        dataMenu* menu = nullptr;
        while (penjual) {
            menu = penjual->headMenu;
            while (menu) {
                if (menu->kodeMenu == kodeMenu) {
                    break;
                }
                menu = menu->next;
            }
            if (menu) {
                break;
            }
            penjual = penjual->next;
        }

        if (menu) {
            buyMenu(currentUser, menu, penjual, jumlah);
        } else {
            cout << "Menu dengan kode " << kodeMenu << " tidak ditemukan." << endl;
        }
    }
}

void showPesanan(dataUser* user) {
    system("cls"); 
    pesanan* curr = user->queuePesananHead;
    pesanan* prev = nullptr;

    if (!curr) {
        cout << "Tidak ada pesanan saat ini" << endl;
        return;
    }

    cout << "Pesanan Masuk:\n";
    while (curr) {
        cout << "ID Pesanan: " << curr->idPesanan << " | Pembeli: " << curr->usernamePembeli << " | Status: " << curr->status << endl;

        int pilihan;
        cout << "1. Tandai Selesai Pesanan\n2. Batalkan Pesanan\nPilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            curr->status = "Complete";
            cout << "Pesanan ditandai selesai!" << endl;
        } else if (pilihan == 2) {
            curr->status = "Cancel";
            cout << "Pesanan ditolak!" << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
            continue;
        }

        // Update histori status
        dataUser* userIter = headUser;
        while (userIter) {
            histori* hist = userIter->stackHistori;
            while (hist) {
            if (hist->idPesanan == curr->idPesanan) {
                hist->status = curr->status;
                hist->sudahDibayar = (pilihan == 1) ? 1 : 2;
                break;
            }
            hist = hist->next;
            }
            userIter = userIter->next;
        }

        // Remove the current pesanan node
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

    cout << "Struk Pembelian" << endl;
    cout << left << setw(18) << "Nama Penjual" 
         << setw(16) << "Kode Menu" 
         << setw(20) << "Nama Menu" 
         << setw(15) << "Jumlah" 
         << setw(15) << "Harga Satuan" 
         << setw(15) << "Status" << endl;

    cout << setfill('=') << setw(120) << "=" << setfill(' ') << endl;

    int totalHarga = 0;
    string currentIdPesanan = "";
    while (curr) {
        if (currentIdPesanan != curr->idPesanan) {
            if (!currentIdPesanan.empty()) {
                cout << setfill('-') << setw(120) << "=" << setfill(' ') << endl;
                cout << "Total Harga: " << "Rp" << totalHarga << endl << endl;
                totalHarga = 0;
                cout << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
            }
            currentIdPesanan = curr->idPesanan;
            cout << "ID Pesanan: " << currentIdPesanan << endl;
        }

        int hargaTotalItem = curr->jumlah * curr->harga; 
        cout << left << setw(18) << curr->namaPenjual
             << setw(16) << curr->kodeMenu
             << setw(20) << curr->namaMenu
             << setw(15) << curr->jumlah << "Rp"
             << setw(13) << curr->harga
             << curr->status << endl;
        totalHarga += hargaTotalItem;

        curr = curr->next;
    }

    if (!currentIdPesanan.empty()) {
        cout << setfill('-') << setw(120) << "=" << setfill(' ') << endl;
        cout << "Total Harga: " << "Rp" << totalHarga << endl;
        cout << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    }
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

    string kode;
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

void sort() {
    int pilihan;
    cout << "\n===============================\n";
    cout << "|         MENU SORTING        |\n";
    cout << "===============================\n";
    cout << "| Pilih metode pengurutan:    |\n";
    cout << "| [1] Merge Sort (Ascending)  |\n";
    cout << "| [2] Quick Sort (Descending) |\n";
    cout << "===============================\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    if (pilihan == 1) {
        dataUser* user = headUser;
        while (user) {
            mergeSortMenu(&user->headMenu);
            user = user->next;
        }
        cout << "Menu berhasil diurutkan secara ascending berdasarkan harga." << endl;
    } else if (pilihan == 2) {
        dataUser* user = headUser;
        while (user) {
            quickSortMenu(&user->headMenu);
            user = user->next;
        }
        cout << "Menu berhasil diurutkan secara descending berdasarkan harga." << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}

void search() {
    int pilihan;
    cout << "\n===============================\n";
    cout << "|         MENU SEARCHING      |\n";
    cout << "===============================\n";
    cout << "|Pilih metode pencarian:      |\n";
    cout << "|[1] Fibonacci Search (harga) |\n";
    cout << "|[2] Jump Search (harga)      |\n";
    cout << "|[3] Boyer-Moore Search (nama)|\n";
    cout << "===============================\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    if (pilihan == 1) {
        // dataUser* user = headUser;
        // mergeSortMenu(&user->headMenu);
        // int harga;
        // cout << "Masukkan harga yang dicari: ";
        // cin >> harga;
        // while (user) {
        //     int index = fibonacciSearch(user->headMenu, harga, length(user->headMenu));
        //     if (index != -1) {
        //         cout << "Menu ditemukan di user " << user->nama << " pada index " << index << endl;
        //     }
        //     user = user->next;
        // }
    } else if (pilihan == 2) {
        // dataUser* user = headUser;
        // mergeSortMenu(&user->headMenu);
        // int harga;
        // cout << "Masukkan harga yang dicari: ";
        // cin >> harga;
        // while (user) {
        //     int index = jumpSearch(user->headMenu, harga, length(user->headMenu));
        //     if (index != -1) {
        //         cout << "Menu ditemukan di user " << user->nama << " pada index " << index << endl;
        //     }
        //     user = user->next;
        // }
    } else if (pilihan == 3) {
        // mergeSortMenu(&headUser->headMenu);
        // string namaMenu;
        // cout << "Masukkan nama menu yang dicari: ";
        // cin.ignore();
        // getline(cin, namaMenu);
        // dataUser* user = headUser;
        // while (user) {
        //     dataMenu* result = boyerMooreSearch(user->headMenu, namaMenu);
        //     if (result) {
        //         cout << "===============================\n"
        //              << "Menu ditemukan!" << endl << "Penjual: " << user->nama << endl 
        //              << "Kode menu: " << result->kodeMenu << endl
        //              << "Nama menu: " << result->namaMenu << endl
        //              << "Harga: Rp" << result->harga << endl
        //              << "===============================\n";
        //     }
        //     user = user->next;
        // }
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}

int main() {
dataUser* penjual1 = new dataUser{"penjual1", "password1", "Penjual", "Stand Penjual 1", nullptr, nullptr, nullptr, nullptr};
dataUser* penjual2 = new dataUser{"penjual2", "password2", "Penjual", "Stand Penjual 2", nullptr, nullptr, nullptr, nullptr};

dataMenu* menu1 = new dataMenu{"M1001", "Nasi Goreng", 15000, nullptr};
dataMenu* menu2 = new dataMenu{"M1002", "Mie Goreng", 12000, nullptr};
dataMenu* menu3 = new dataMenu{"M1003", "Ayam Bakar", 20000, nullptr};
dataMenu* menu4 = new dataMenu{"M1004", "Sate Ayam", 18000, nullptr};

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
                                    cout << "\n========================" << endl;
                                    cout << "[1] Urutkan Menu" << endl;
                                    cout << "[2] Cari Menu" << endl;
                                    cout << "[3] Kembali" << endl;
                                    cout << "==========================" << endl;
                                    cout << "Masukkan pilihan: ";
                                    cin >> pilihan;
                                    if (pilihan == 1){
                                        sort();
                                    } else if (pilihan == 2){
                                        search();
                                    } else if (pilihan == 3){
                                        break;
                                    } else {
                                        cout << "Pilihan tidak valid." << endl;
                                        cin.clear();
                                        cin.ignore(INT_MAX, '\n');
                                        Sleep(500);
                                    }
                                    system("pause");
                                }
                                break;
                            case 2:
                                addMenu(currentUser);
                                break;
                            case 3:
                                ubahmenu(currentUser);
                                break;
                            case 4:
                                delMenuAwal(currentUser);
                                break;
                            case 5:
                                delMenu(currentUser);
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
                        if (subPilihanPenjual != 7) {
                            system("pause");
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
                                while (true){
                                    showMenu();
                                    int pilihan;
                                    cout << "\n========================" << endl;
                                    cout << "[1] Urutkan Menu" << endl;
                                    cout << "[2] Cari Menu" << endl;
                                    cout << "[3] Kembali" << endl;
                                    cout << "==========================" << endl;
                                    cout << "Masukkan pilihan: ";
                                    cin >> pilihan;
                                    if (pilihan == 1){
                                        sort();
                                    } else if (pilihan == 2){
                                        search();
                                    } else if (pilihan == 3){
                                        break;
                                    } else {
                                        cout << "Pilihan tidak valid." << endl;
                                        cin.clear();
                                        cin.ignore(INT_MAX, '\n');
                                        Sleep(500);
                                    }
                                    system("pause");
                                }
                                break;
                            case 2: {
                                showMenu();
                                beli(currentUser, headUser);
                            }
                            break;
                            case 3:
                                showHistory(currentUser);
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
                        if (subPilihanPembeli != 4) {
                            system("pause");
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