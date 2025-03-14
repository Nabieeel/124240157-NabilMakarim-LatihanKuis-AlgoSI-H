#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Buku
{
    int id;
    char judul[100];
    char penulis[100];
    int stok;
};

bool login()
{
    string username, inputUser;
    string password, inputPass;

    cout << "Masukkan username: ";
    cin >> inputUser;
    cout << "Masukkan password: ";
    cin >> inputPass;

    username = "nabil";
    password = "157";

    return (inputUser == username && inputPass == password);
}

void tambahBuku()
{
    Buku buku;
    ofstream file("data.dat", ios::app | ios::binary);

    cout << "Masukkan ID Buku: ";
    cin >> buku.id;
    cin.ignore();
    cout << "Masukkan Judul Buku: ";
    cin.getline(buku.judul, 100);
    cout << "Masukkan Penulis: ";
    cin.getline(buku.penulis, 100);
    cout << "Masukkan Stok Buku: ";
    cin >> buku.stok;

    file.write(reinterpret_cast<char *>(&buku), sizeof(Buku));
    file.close();

    cout << "Data buku berhasil ditambahkan!\n";
}

void tampilkanBuku()
{
    vector<Buku> daftarBuku;
    Buku buku;
    ifstream file("data.dat", ios::binary);

    while (file.read(reinterpret_cast<char *>(&buku), sizeof(Buku)))
    {
        daftarBuku.push_back(buku);
    }
    file.close();

    // Bubble Sort berdasarkan ID
    for (size_t i = 0; i < daftarBuku.size() - 1; i++)
    {
        for (size_t j = 0; j < daftarBuku.size() - i - 1; j++)
        {
            if (daftarBuku[j].id > daftarBuku[j + 1].id)
            {
                swap(daftarBuku[j], daftarBuku[j + 1]);
            }
        }
    }

    cout << "\nDaftar Buku:\n";
    for (const auto &b : daftarBuku)
    {
        cout << "ID: " << b.id << " | Judul: " << b.judul << " | Penulis: " << b.penulis << " | Stok: " << b.stok << "\n";
    }
}

void cariBuku()
{
    char keyword[100];
    Buku buku;
    ifstream file("data.dat", ios::binary);
    bool ditemukan = false;

    cout << "Masukkan kata kunci judul: ";
    cin.ignore();
    cin.getline(keyword, 100);

    while (file.read(reinterpret_cast<char *>(&buku), sizeof(Buku)))
    {
        if (strstr(buku.judul, keyword))
        {
            cout << "Buku ditemukan!\n";
            cout << "ID: " << buku.id << " | Judul: " << buku.judul << " | Penulis: " << buku.penulis << " | Stok: " << buku.stok << "\n";
            ditemukan = true;
        }
    }
    file.close();

    if (!ditemukan)
    {
        cout << "Buku tidak ditemukan.\n";
    }
}

void hapusBuku()
{
    int idHapus;
    vector<Buku> daftarBuku;
    Buku buku;
    ifstream file("data.dat", ios::binary);

    cout << "Masukkan ID buku yang ingin dihapus: ";
    cin >> idHapus;

    while (file.read(reinterpret_cast<char *>(&buku), sizeof(Buku)))
    {
        if (buku.id != idHapus)
        {
            daftarBuku.push_back(buku);
        }
    }
    file.close();

    ofstream outFile("data.dat", ios::binary | ios::trunc);
    for (const auto &b : daftarBuku)
    {
        outFile.write(reinterpret_cast<const char *>(&b), sizeof(Buku));
    }
    outFile.close();

    cout << "Buku berhasil dihapus jika ID ditemukan.\n";
}

int main()
{
    if (!login())
    {
        cout << "Login gagal. Coba lagi!\n";
        return 0;
    }

    int pilihan;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Tambah Buku\n2. Tampilkan Buku\n3. Cari Buku\n4. Hapus Buku\n5. Keluar\nPilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahBuku();
            break;
        case 2:
            tampilkanBuku();
            break;
        case 3:
            cariBuku();
            break;
        case 4:
            hapusBuku();
            break;
        case 5:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);

    return 0;
}
