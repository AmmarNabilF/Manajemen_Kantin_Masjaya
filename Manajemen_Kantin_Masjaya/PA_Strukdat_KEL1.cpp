#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

struct menu{
    string nama_menu;
    int harga;
    int stok;
    string kategori;
};

struct antrean{
    string nama;
    int umur;
    string status;
};

struct node {
    menu makanan;
    antrean orang;
    node *next;
    node *prev;
};

node *head = NULL;
node *last = NULL;

bool kosong() {
    return head == NULL;
}

// ================================================== FIBONACCI SEARCH AREAS ==================================================

int length(node *head){
    int count = 0;
    node *temp = head;
    while (temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

int min(int x, int y){
    return (x <= y) ? x : y;
}

int fibonacciSearch(node *head, int x, int n ){
    node *temp = head;
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    while (fibM < n){
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1){
        int i = min(offset + fibMMm2, n - 1);

        temp = head;
        for (int j = 0; j < i; j++){
            if (temp == NULL){
                break;
            }
            temp = temp->next;
        }
        if (temp->makanan.harga < x){
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (temp->makanan.harga > x){
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }
    if (fibMMm1 && temp->makanan.harga == x){
        return offset + 1;
    }
    return -1;
}

// ================================================== JUMP SEARCH AREAS ==================================================

int findNode(node *head, int idx){
    node *temp = head;
    for (int i = 0; i < idx; i++){
        if (temp == NULL){
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL){
        return 0;
    }
    return temp->orang.umur;
}

int jumpSearch(node *head, int x, int n){
    
    int step = sqrt(n);
    int prev = 0;
    while (findNode(head, min(step, n) - 1) < x){
        prev = step;
        step += sqrt(n);
        if (prev >= n){
            return -1;
        }
    }
    while (findNode(head, prev) < x){
        prev++;
        if (prev == min(step, n)){
            return -1;
        }
    }
    if (findNode(head, prev) == x){
        return prev;
    }
    return -1;
}

// ================================================== BOYER-MOORE SEARCH AREAS ==================================================

const int NO_OF_CHARS = 256;

void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS]){
    for (int i = 0; i < NO_OF_CHARS; i++){
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++){
        badChar[(int)str[i]] = i;
    }
}

void search(node *head, string pat){
    int m = pat.size();
    node *temp = head;
    while (temp != NULL){
        int n = temp->makanan.nama_menu.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);
        int s = 0;
        while (s <= (n - m)){
            int j = m - 1;
            while (j >= 0 && pat[j] == temp->makanan.nama_menu[s + j]){
                j--;
            }
            if (j < 0){
                cout << temp->makanan.nama_menu << endl;
                break;
            } else {
                s += max(1, j - badChar[temp->makanan.nama_menu[s + j]]);
            }
        }
        temp = temp->next;
    }
}

// ================================================== QUICKSORT AREAS ==================================================

void tukar_menu(node *a, node *b){
    menu temp = a->makanan;
    a->makanan = b->makanan;
    b->makanan = temp;
}

node *partition_harga(node* low, node* high){
    int pivot = high->makanan.harga;
    node *i = low->prev;
    for (node *j = low; j != high; j = j->next){
        if (j->makanan.harga < pivot){
            i = (i == NULL) ? low : i->next;
            tukar_menu(i, j);
        }
    }
    i = (i == NULL) ? low : i->next;
    tukar_menu(i, high);
    return i;
}

void quickSort_harga(node* low, node* high){
    if (high != NULL && low != high && low != high->next){
        node *pi = partition_harga(low, high);
        quickSort_harga(low, pi->prev);
        quickSort_harga(pi->next, high);
    }
}

// ================================================== SHELLSORT AREAS ==================================================

void tukar_antrean(node *front, node *rear){
    antrean temp = front->orang;
    front->orang = rear->orang;
    rear->orang = temp;
}

void shellSort_umur(node *front, int n){
    for (int gap = n/2; gap > 0; gap /= 2){
        for (node *i = front; i != NULL; i = i->next){
            for (node *j = i->next; j != NULL; j = j->next){
                if (i->orang.umur < j->orang.umur){
                    tukar_antrean(i, j);
                }
            }
        }
    }
}

// ================================================== MAIN AREAS ==================================================
node* tambah_antrean(){
    antrean orang;
    cout << "" << endl;
    cout << "Masukkan nama : ";
    getline(cin >> ws, orang.nama);
    cout << "Masukkan umur : ";
    cin >> orang.umur;
    cout << "Masukkan status : ";
    getline(cin >> ws, orang.status);

    node *baru = new node;
    baru->orang = orang;
    baru->next = NULL;
    baru->prev = NULL;
    return baru;
}

void masuk_antrean(node** front, node** rear){
    node *baru = tambah_antrean();
    if (*front == NULL) {
        *front = baru;
        *rear = baru;
    } else {
        baru->prev = *rear;
        (*rear)->next = baru;
        *rear = baru;
    }
}

void cancel_antrean(node** front, node** rear){
    if (*front == NULL) {
        cout << "Queue Underflow !!" << endl;
        return;
    } else if ((*front)->next == NULL) {
        delete *front;
        *front = NULL;
        *rear = NULL;
    } else {
        node *temp = *front;
        *front = (*front)->next;
        (*front)->prev = NULL;
        delete temp;
    }
}

void show(node* front){
    if (front == NULL) {
        cout << "Queue Underflow !!" << endl;
        return;
    }
    while (front != NULL) {
        cout << "" << endl;
        cout << "Nama : " << front->orang.nama << endl;
        cout << "Umur : " << front->orang.umur << endl;
        cout << "Status : " << front->orang.status << endl;
        front = front->next;
    }
}

node* tambah_menu() {
    cout << "" << endl;
    node *baru = new node;
    cout << "Masukkan nama menu : ";
    getline(cin >> ws, baru->makanan.nama_menu);
    cout << "Masukkan harga : ";
    cin >> baru->makanan.harga;
    cout << "Masukkan stok : ";
    cin >> baru->makanan.stok;
    cout << "Masukkan kategori : ";
    getline(cin >> ws, baru->makanan.kategori);
    baru->next = NULL;
    baru->prev = NULL;
    return baru;
}

void push_menu(node** top) {
    node *baru = tambah_menu();
    if (*top == NULL) {
        *top = baru;
    } else {
        baru->next = *top;
        (*top)->prev = baru;
        *top = baru;
    }
}

void pop_menu(node** top) {
    if (*top == NULL) {
        cout << "Stack Underflow !!" << endl;
        return;
    } else if ((*top)->next == NULL) {
        delete *top;
        *top = NULL;
    } else {
        node *temp = *top;
        *top = (*top)->next;
        (*top)->prev = NULL;
        delete temp;
    }
}

void peek_menu(node* top) {
    if (top == NULL || top->next == NULL) {
        cout << "Stack Underflow !!" << endl;
        return;
    }
    while (top != NULL) {
        cout << "" << endl;
        cout << "Nama menu : " << top->makanan.nama_menu << endl;
        cout << "Harga : " << top->makanan.harga << endl;
        cout << "Stok : " << top->makanan.stok << endl;
        cout << "Kategori : " << top->makanan.kategori << endl;
        top = top->next;

    }
}

int hitung_perulangan(node* top){
    int hitung = 0;
    while (top != NULL) {
        hitung++;
        top = top->next;
    }
    return hitung;
}

int hitung_perulangan2(node* front){
    int hitung = 0;
    while (front != NULL) {
        hitung++;
        front = front->next;
    }
    return hitung;
}

int main(){
    int ygdicari, simpannilai, indeks;
    string pat;

    node *top = NULL;
    node *front = NULL;
    node *rear = NULL;
    int pilihan;
    

        while (true) {

            cout << "" << endl;
            cout << "1. Tambah antrean" << endl;
            cout << "2. Batal antrean" << endl;
            cout << "3. Lihat antrean" << endl;
            cout << "4. Tambah menu" << endl;
            cout << "5. Hapus menu" << endl;
            cout << "6. Lihat menu" << endl;
            cout << "7. Urutkan menu dari harga (asc)" << endl;    
            cout << "8. Urutkan antrean dari umur (desc)" << endl;
            cout << "9. Cari harga dari menu yang ada(fibonacci)" << endl;
            cout << "10.Cari pelanggan dari umur(jump)" << endl;
            cout << "11.Cari menu dari nama menu (boyer-moore)" << endl;
            cout << "12.Exit" << endl;
            cout << "" << endl;
            cout << "Masukkan pilihan : ";
            cin >> pilihan;

            switch (pilihan){
                case 1: 
                    masuk_antrean(&front, &rear);
                    break;
                case 2:
                    cancel_antrean(&front, &rear);
                    break;
                case 3:
                    show(front);
                    break;
                case 4:
                    push_menu(&top);
                    break;
                case 5:
                    pop_menu(&top);
                    break;
                case 6:
                    peek_menu(top);
                    break;
                case 7:
                {
                    node* last = top;
                    while (last->next != NULL) {
                        last = last->next;
                    }
                    quickSort_harga(top, last);
                    if (top != NULL) {
                        peek_menu(top);
                    }
                    else {
                        cout << "Tidak ada menu" << endl;
                    }
                }                
                break;
                case 8:
                {
                    int n = hitung_perulangan2(front);
                    if (n > 0) {
                        shellSort_umur(front, n);
                        show(front);
                    }
                    else {
                        cout << "Tidak ada antrean" << endl;
                    }
                }
                break;

                case 9:
                {   
                    int n = hitung_perulangan(top);
                    if (n > 0) {
                        node *last = top;
                        while (last->next != NULL) {
                            last = last->next;
                        }
                        cout << "Masukkan harga yang dicari : ";
                        cin >> ygdicari;
                        int hasil = fibonacciSearch(top, ygdicari, n);
                        if (hasil == -1) {
                            cout << "Data tidak ditemukan" << endl;
                        }
                        else {
                            cout << "Data ditemukan pada indeks ke-" << hasil << endl;
                        }
                    }
                    else {
                        cout << "Tidak ada menu" << endl;
                    }
                }
                    break;

                case 10:
                {
                    int n = hitung_perulangan2(front);
                    if (n > 0) {
                        cout << "Masukkan umur yang dicari : ";
                        cin >> simpannilai;
                        indeks = jumpSearch(front, simpannilai, n);
                        if (indeks == -1) {
                            cout << "Data tidak ditemukan" << endl;
                        }
                        else {
                            cout << "Data ditemukan pada indeks ke-" << indeks << endl;
                        }
                    }
                    else {
                        cout << "Tidak ada antrean" << endl;
                    }
                }
                    break;

                case 11:
                {
                    string pat;
                    cout << "Masukkan nama menu yang dicari : ";
                    getline(cin >> ws, pat);
                    cout << "Menu yang ditemukan : " << endl;
                    search(top, pat);
                }
                    break;

                case 12:
                    exit(0);
                    break;
            }    
    }

    return 0;
}

