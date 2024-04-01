#include <iostream>
#include <cstring>
using namespace std;

// Struct untuk menyimpan informasi buku
struct Buku {
    char judul[100];
    char penulis[50];
    int tahunTerbit;
    bool tersedia;
    Buku* next; // Pointer untuk linked list
};

// Fungsi untuk menampilkan informasi buku
void tampilkanBuku(const Buku* buku) {
    cout << "Judul: " << buku->judul << endl;
    cout << "Penulis: " << buku->penulis << endl;
    cout << "Tahun Terbit: " << buku->tahunTerbit << endl;
    cout << (buku->tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
}

// Fungsi untuk menambahkan buku ke linked list
void tambahBuku(Buku* &head, const char* judul, const char* penulis, int tahunTerbit, bool tersedia) {
    Buku* baru = new Buku;
    strcpy(baru->judul, judul);
    strcpy(baru->penulis, penulis);
    baru->tahunTerbit = tahunTerbit;
    baru->tersedia = tersedia;
    baru->next = nullptr;

    if (!head) {
        head = baru;
    } else {
        Buku* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

// Fungsi untuk meminjam buku dari linked list
void pinjamBuku(Buku* head, const char* judul) {
    Buku* temp = head;
    while (temp) {
        if (strcmp(temp->judul, judul) == 0) {
            if (temp->tersedia) {
                temp->tersedia = false;
                cout << "Buku berhasil dipinjam.\n";
                cout << "Selamat membaca :)\n";
                return;
            } else {
                cout << "Yahhh, buku ini sudah dipinjam, silahkan pilih buku lain :(\n";
                return;
            }
        }
        temp = temp->next;
    }
    cout << "Maaf, buku ini tidak tersedia di Perpustakaan.\n";
}

// Fungsi untuk mengembalikan buku yang dipinjam
void kembalikanBuku(Buku* head, const char* judul) {
    Buku* temp = head;
    while (temp) {
        if (strcmp(temp->judul, judul) == 0) {
            if (!temp->tersedia) {
                temp->tersedia = true;
                cout << "Buku berhasil dikembalikan. Terima kasih :)\n";
                return;
            } else {
                cout << "Buku sudah tersedia di perpustakaan.\n";
                return;
            }
        }
        temp = temp->next;
    }
    cout << "Maaf, buku tidak ditemukan.\n";
}

int main() {
    Buku* daftarBuku = nullptr; // Pointer untuk linked list

    tambahBuku(daftarBuku, "Harry Potter", "J.K. Rowling", 2005, true);
    tambahBuku(daftarBuku, "Lord of the Rings", "J.R.R. Tolkien", 2003, false);
    tambahBuku(daftarBuku, "Laskar Pelangi", "Andrea Hirata", 2005, false);
    tambahBuku(daftarBuku, "Dilan: Dia adalah Dilanku Tahun 1990", "Pidi Baiq", 2014, true);
    tambahBuku(daftarBuku, "Dilan Bagian Kedua: Dia adalah Dilanku Tahun 1991", "Pidi Baiq", 2015, true);
    tambahBuku(daftarBuku, "Milea: Suara dari Dilan", "Pidi Baiq", 2016, true);
    tambahBuku(daftarBuku, "Ancika: Dia yang Bersamaku Tahun 1995", "Pidi Baiq", 2021, false);

    while (true) {
        cout << endl;
        cout << "===== Selamat Datang di Perpustakaan =====\n\n";
        cout << "==============================\n";
        cout << "|        Pilihan Menu        |\n";
        cout << "==============================\n";
        cout << "|[1]. Tampilkan Daftar Buku  |\n";
        cout << "|[2]. Pinjam Buku            |\n";
        cout << "|[3]. Kembalikan Buku        |\n";
        cout << "|[4]. Keluar                 |\n";
        cout << "==============================\n";
        cout << "Pilih menu: ";
        
        int pilihan;
        cin >> pilihan;

        switch (pilihan) {
            case 1: // Tampilkan Daftar Buku
                if (!daftarBuku) {
                    cout << "Maaf, saat ini idak ada buku yang tersedia :(\n";
                    cout << "Silahkan datang di lain waktu ^_^\n";
                } else {
                    cout << endl;
                    cout << "===== Daftar Buku =====\n\n";
                    Buku* temp = daftarBuku;
                    while (temp) {
                        tampilkanBuku(temp);
                        cout << endl;
                        temp = temp->next;
                    }
                }
                break;
            case 2: // Pinjam Buku
                cout << endl;
                cout << "Masukkan judul buku yang ingin dipinjam: ";
                char judulPinjam[100];
                cin.ignore();
                cin.getline(judulPinjam, 100);
                pinjamBuku(daftarBuku, judulPinjam);
                break;
            case 3: // Kembalikan Buku
                cout << endl;
                cout << "Masukkan judul buku yang ingin dikembalikan: ";
                char judulKembali[100];
                cin.ignore();
                cin.getline(judulKembali, 100);
                kembalikanBuku(daftarBuku, judulKembali);
                break;
            case 4: // Keluar
                cout << endl;
                cout << "Terima kasih sudah berkunjung ke perpustakaan.\n";
                cout << "Sampai jumpa lagi ^_^\n";
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan pilih menu yang sesuai.\n";
                break;
        }
    }

    // Dealokasi memori yang dialokasikan untuk linked list
    Buku* temp = daftarBuku;
    while (temp) {
        Buku* next = temp->next;
        delete temp;
        temp = next;
    }

    return 0;
}
