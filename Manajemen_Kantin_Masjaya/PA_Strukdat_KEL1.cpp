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

// void splitMenuList(dataMenu* source, dataMenu** frontRef, dataMenu** backRef) {
//     dataMenu* fast;
//     dataMenu* slow;
//     slow = source;
//     fast = source->next;

//     while (fast != nullptr) {
//         fast = fast->next;
//         if (fast != nullptr) {
//             slow = slow->next;
//             fast = fast->next;
//         }
//     }

//     *frontRef = source;
//     *backRef = slow->next;
//     slow->next = nullptr;
// }

// dataMenu* mergeSortedMenu(dataMenu* a, dataMenu* b) {
//     dataMenu* result = nullptr;

//     if (a == nullptr)
//         return b;
//     else if (b == nullptr)
//         return a;

//     if (a->harga <= b->harga) {
//         result = a;
//         result->next = mergeSortedMenu(a->next, b);
//     } else {
//         result = b;
//         result->next = mergeSortedMenu(a, b->next);
//     }

//     return result;
// }

// void mergeSortMenu(dataMenu** headRef) {
//     if (*headRef == nullptr || (*headRef)->next == nullptr)
//         return;

//     dataMenu* head = *headRef;
//     dataMenu* a;
//     dataMenu* b;

//     splitMenuList(head, &a, &b);

//     mergeSortMenu(&a);
//     mergeSortMenu(&b);

//     *headRef = mergeSortedMenu(a, b);
// }

// histori* getTail(histori* curr) {
//     while (curr && curr->next) {
//         curr = curr->next;
//     }
//     return curr;
// }

// histori* partition(histori* head, histori* end, histori** newHead, histori** newEnd) {
//     histori* pivot = end;
//     histori* prev = nullptr;
//     histori* curr = head;
//     histori* tail = pivot;

//     while (curr != pivot) {
//         if (curr->harga < pivot->harga) {
//             if ((*newHead) == nullptr) {
//                 (*newHead) = curr;
//             }
//             prev = curr;
//             curr = curr->next;
//         } else {
//             if (prev != nullptr) {
//                 prev->next = curr->next;
//             }
//             histori* temp = curr->next;
//             curr->next = nullptr;
//             tail->next = curr;
//             tail = curr;
//             curr = temp;
//         }
//     }

//     if ((*newHead) == nullptr) {
//         (*newHead) = pivot;
//     }

//     (*newEnd) = tail;
//     return pivot;
// }

// histori* quickSortRecur(histori* head, histori* end) {
//     if (!head || head == end)
//         return head;

//     histori* newHead = nullptr;
//     histori* newEnd = nullptr;

//     histori* pivot = partition(head, end, &newHead, &newEnd);

//     if (newHead != pivot) {
//         histori* temp = newHead;
//         while (temp->next != pivot)
//             temp = temp->next;
//         temp->next = nullptr;

//         newHead = quickSortRecur(newHead, temp);

//         temp = getTail(newHead);
//         temp->next = pivot;
//     }

//     pivot->next = quickSortRecur(pivot->next, newEnd);

//     return newHead;
// }

// void quickSortHistori(histori** headRef) {
//     (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
// }

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
    cout << "      SILAHKAN REGISTRASI" << endl;
    cout << "===============================" << endl;
    cout << "[1] Register Sebagai Penjual" << endl;
    cout << "[2] Register Sebagai Pembeli" << endl;
    cout << "===============================" << endl;
    cout << "Masukkan pilihan: ";
    int pilih;
    cin >> pilih;
    system("cls");
    if (pilih == 1){
        cout << "Username: ";
        cin >> user;
        dataUser* data = headUser;
        while (data) {
            if (data->username == user) {
                cout << "Username Telah Dipakai Akun Lain" << endl;
                return;
            }
            data = data->next;
        }
        cin.ignore();
        cout << "Nama Stand: ";
        getline(cin, nama);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        Sleep(500);
    } else if (pilih == 2){
        cout << "Username: ";
        cin >> user;
        dataUser* data = headUser;
        while (data) {
            if (data->username == user) {
                cout << "Username Telah Dipakai Akun Lain" << endl;
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
        cout << "Registrasi Berhasil!" << endl;
        Sleep(500);
    } else {
        cout << "Pilihan tidak valid" << endl;
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
    cout << "\nLogin Menu\nUsername: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    dataUser* data = headUser;
    while (data) {
        if (data->username == user && data->password == pass) {
            cout << "Login Berhasil :D" << endl;
            Sleep(500);
            return data;
        }
        data = data->next;
    }

    cout << "Login Gagal :(" << endl;
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

void addMenu(dataUser* user, bool addAwal) {
    system("cls");
    string namaMenu;
    cin.clear();
    cin.ignore();
    cout << "\nNama Menu: ";
    getline(cin, namaMenu);

    int harga = inputHarga();
    string kodeMenu = generateKodeMenu();

    dataMenu* newMenu = new dataMenu{kodeMenu, namaMenu, harga, nullptr};

    if (addAwal || !user->headMenu) {
        newMenu->next = user->headMenu;
        user->headMenu = newMenu;
    } else {
        dataMenu* curr = user->headMenu;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newMenu;
    }

    cout << "Menu berhasil ditambahkan" << (addAwal ? " di awal." : " di akhir.") << endl;
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
    cout << "\n" << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(27) << "=" << setfill(' ') << "      Menu Makanan     " << setfill('=') << setw(27) << "=" << setfill(' ') << endl;
    cout << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
    cout << left << setw(20) << "Nama Penjual" << setw(11) << "Kode Menu" << setw(20) << "Nama Menu" << setw(20) << "Harga" << endl;
    cout << setfill('=') << setw(81) << "=" << setfill(' ') << endl;
    
    dataUser* userSekarang = headUser;
    while (userSekarang) {
        mergeSortedMenu(&userSekarang->headMenu);
        dataMenu* menu = userSekarang->headMenu;
        while (menu) {
            cout << left << setw(20) << userSekarang->nama
                 << setw(11) << menu->kodeMenu
                 << setw(20) << menu->namaMenu
                 << "Rp" << menu->harga << endl;
            menu = menu->next;
        }
        userSekarang = userSekarang->next;
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
    
    // quickSortHistori(&user->stackHistori);

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
             << setw(15) << curr->jumlah
             << setw(15) << "Rp" << curr->harga
             << setw(15) << curr->status << endl;
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
        cout << "1. Registrasi\n2. Login\n3. Keluar\nPilihan: ";
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
                        cout << "1. Lihat Menu Anda\n2. Tambah Menu\n3. Ubah Menu\n4. Hapus Menu\n5. Lihat Pesanan\n6. Logout\nPilihan: ";
                        cin >> subPilihanPenjual;

                        switch (subPilihanPenjual) {
                            case 1:
                                showMenuPenjual(currentUser);
                                break;
                            case 2:
                                addMenu(currentUser, false);
                                break;
                            case 3:
                                ubahmenu(currentUser);
                                break;
                            case 4:
                                delMenu(currentUser);
                                break;
                            case 5:
                                showPesanan(currentUser);
                                break;
                            case 6:
                                currentUser = nullptr;
                                break;
                            default:
                                cout << "Pilihan tidak valid." << endl;
                                break;
                        }
                        if (subPilihanPenjual != 6) {
                            system("pause");
                        }
                    } while (subPilihanPenjual != 6);
                } else if (currentUser->role == "Pembeli") {
                    int subPilihanPembeli;
                    do {
                        system("cls");
                        cout << "1. Lihat Menu\n2. Beli Menu\n3. Lihat Riwayat Pembelian\n4. Logout\nPilihan: ";
                        cin >> subPilihanPembeli;

                        switch (subPilihanPembeli) {
                            case 1:
                                showMenu();
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
                break;
        }
    }
}