#include <iostream>

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
    FILE* file = fopen("data.dat", "ab");

    cout << "Masukkan ID Buku: ";
    cin >> buku.id;
    cin.ignore();
    cout << "Masukkan Judul Buku: ";
    cin.getline(buku.judul, 100);
    cout << "Masukkan Penulis: ";
    cin.getline(buku.penulis, 100);
    cout << "Masukkan Stok Buku: ";
    cin >> buku.stok;

    fwrite(&buku, sizeof(Buku), 1, file);
    fclose(file);

    cout << "Data buku berhasil ditambahkan!\n";
}

void tampilkanBuku()
{
    Buku buku;
    FILE* file = fopen("data.dat", "rb");
    Buku daftarBuku[100];
    int count = 0;

    while (fread(&buku, sizeof(Buku), 1, file))
    {
        daftarBuku[count++] = buku;
    }
    fclose(file);

    // Bubble Sort berdasarkan ID
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (daftarBuku[j].id > daftarBuku[j + 1].id)
            {
                Buku temp = daftarBuku[j];
                daftarBuku[j] = daftarBuku[j + 1];
                daftarBuku[j + 1] = temp;
            }
        }
    }

    cout << "\nDaftar Buku:\n";
    for (int i = 0; i < count; i++)
    {
        cout << "ID: " << daftarBuku[i].id << " | Judul: " << daftarBuku[i].judul 
             << " | Penulis: " << daftarBuku[i].penulis << " | Stok: " << daftarBuku[i].stok << "\n";
    }
}

void cariBuku()
{
    char keyword[100];
    Buku buku;
    FILE* file = fopen("data.dat", "rb");
    bool ditemukan = false;

    cout << "Masukkan kata kunci judul: ";
    cin.ignore();
    cin.getline(keyword, 100);

    while (fread(&buku, sizeof(Buku), 1, file))
    {
        bool match = false;
        char* ptr = buku.judul;
        char* keyptr = keyword;
        
        while (*ptr && *keyptr) {
            if (tolower(*ptr) == tolower(*keyptr)) {
                ptr++;
                keyptr++;
            } else {
                break;
            }
        }
        
        if (*keyptr == '\0') {
            match = true;
        }

        if (match)
        {
            cout << "Buku ditemukan!\n";
            cout << "ID: " << buku.id << " | Judul: " << buku.judul 
                 << " | Penulis: " << buku.penulis << " | Stok: " << buku.stok << "\n";
            ditemukan = true;
        }
    }
    fclose(file);

    if (!ditemukan)
    {
        cout << "Buku tidak ditemukan.\n";
    }
}

void hapusBuku()
{
    int idHapus;
    Buku buku;
    FILE* file = fopen("data.dat", "rb");
    Buku daftarBuku[100];
    int count = 0;

    cout << "Masukkan ID buku yang ingin dihapus: ";
    cin >> idHapus;

    while (fread(&buku, sizeof(Buku), 1, file))
    {
        if (buku.id != idHapus)
        {
            daftarBuku[count++] = buku;
        }
    }
    fclose(file);

    file = fopen("data.dat", "wb");
    for (int i = 0; i < count; i++)
    {
        fwrite(&daftarBuku[i], sizeof(Buku), 1, file);
    }
    fclose(file);

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
