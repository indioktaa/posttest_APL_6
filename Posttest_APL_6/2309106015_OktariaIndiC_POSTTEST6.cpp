#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;

const int max_produk = 10;

struct Data {
    string tujuaninvestasi;
    string tanggalbeli;
};

struct Pembeli {
    string namapembeli;
    double number;
};

struct Produk {
    string nama;
    double oneyearreturn;
    Data data;
    Pembeli pembeli;
    bool sort = false;
    Produk *unsortDat[max_produk];

    void tampilkan(Produk *produkPtr[], int posisi) {
        system("cls");
        if (posisi > 0) {
            cout << "Data investasi tersimpan" << endl;
            for (int a = 0; a < posisi; a++) {
                cout << a + 1 << ". " << produkPtr[a]->nama << " 1 year return: "<< produkPtr[a]->oneyearreturn << "%" << endl;
                cout << "tujuan pembelian: " << produkPtr[a]->data.tujuaninvestasi << endl;
                cout << "tanggal pembelian: " << produkPtr[a]->data.tanggalbeli << endl;
                cout << "nama pembeli: " << produkPtr[a]->pembeli.namapembeli << endl;
                cout << "Nomor telfon: " << fixed << setprecision(0) << produkPtr[a]->pembeli.number << endl;
            }
        } else {
            cout << "====== ANDA BELUM INVESTASI ======" << endl;
        }
    }

    void tambahdata(Produk *produkPtr[], int &posisi) {
        string ulang;
        do {
            tampilkan(produkPtr, posisi);
            if (posisi >= max_produk) {
                cout << "Maaf, anda sudah mencapai batas maksimum investasi" << endl;
                return;
            }

            produkPtr[posisi] = new Produk;

            cout << "Masukkan data produk investasi baru:\n";

            cout << "Nama: ";
            cin.ignore();
            getline(cin, produkPtr[posisi]->nama);

            cout << "1 Year Return (%): ";
            cin >> produkPtr[posisi]->oneyearreturn;

            cout << "Apa tujuan pembelian anda: ";
            cin.ignore();
            getline(cin, produkPtr[posisi]->data.tujuaninvestasi);

            cout << "Tanggal pembelian: ";
            getline(cin, produkPtr[posisi]->data.tanggalbeli);

            cout << "Silahkan masukan nama anda: ";
            getline(cin, produkPtr[posisi]->pembeli.namapembeli);

            cout << "Silahkan masukan nomor telfon anda: ";
            cin >> produkPtr[posisi]->pembeli.number;

            cout << "Produk berhasil ditambahkan.\n";
            posisi++;

            cout << "Tambah data lagi? (y/n): ";
            cin >> ulang;

        } while (ulang == "y" || ulang == "Y");
    }

    void perbarui(Produk *produkPtr[], int posisi) {
        string ulang;
        int i;
        do {
            tampilkan(produkPtr, posisi);
            cout << "Ubah data ke : ";
            cin >> i;
            cin.ignore();
            i--;
            cout << "Ubah menjadi: ";
            getline(cin, produkPtr[i]->nama);

            cout << "1 year return (%): ";
            cin >> produkPtr[i]->oneyearreturn;

            cin.ignore();
            cout << "Ubah tujuan pembelian: ";
            getline(cin, produkPtr[i]->data.tujuaninvestasi);

            cout << "Data berhasil diperbarui.";
            tampilkan(produkPtr, posisi);
            cout << "Apakah mau ubah lagi? (y/n): ";
            cin >> ulang;
            i = -1;
        } while (ulang == "y");
    }

    void hapusdata(Produk *produkPtr[], int &posisi) {
        string ulang;
        int j;
        do {
            tampilkan(produkPtr, posisi);
            if (posisi > 0) {
                cout << "Hapus data ke: ";
                cin >> j;
                cin.ignore();

                if (j >= 1 && j <= posisi) {
                    delete produkPtr[j - 1];
                    for (int i = j - 1; i < posisi - 1; ++i) {
                        produkPtr[i] = produkPtr[i + 1];
                    }
                    posisi--;
                    tampilkan(produkPtr, posisi);
                } else {
                    cout << "Pilihan yang anda masukan salah";
                }
                cout << "Hapus lagi (y/n): ";
                cin >> ulang;
            } else {
                cout << "Tidak ada yang bisa anda hapus";
                cout << "Isi n : ";
                cin >> ulang;
            }
        } while (ulang == "y");
    }

    void bubbleSortAscending(Produk *produkPtr[], int posisi) {
        for (int i = 0; i < posisi - 1; i++) {
            for (int j = 0; j < posisi - i - 1; j++) {
                if (produkPtr[j]->nama > produkPtr[j + 1]->nama) {
                    swap(produkPtr[j], produkPtr[j + 1]);
                }
            }
        }
        sort = true;
    }

    void quickSortDescending(Produk *produkPtr[], int low, int high) {
        if (low < high) {
            int pi = partition(produkPtr, low, high);
            quickSortDescending(produkPtr, low, pi - 1);
            quickSortDescending(produkPtr, pi + 1, high);
        }
        sort = true;
    }

    int partition(Produk *produkPtr[], int low, int high) {
        double pivot = produkPtr[high]->oneyearreturn;
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (produkPtr[j]->oneyearreturn > pivot) {
                i++;
                swap(produkPtr[i], produkPtr[j]);
            }
        }
        swap(produkPtr[i + 1], produkPtr[high]);
        return (i + 1);
    }

    void shellSortAscending(Produk *produkPtr[], int posisi) {
        for (int gap = posisi / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < posisi; i++) {
                Produk* temp = produkPtr[i];
                int j;
                for (j = i; j >= gap && produkPtr[j - gap]->pembeli.number > temp->pembeli.number; j -= gap) {
                    produkPtr[j] = produkPtr[j - gap];
                }
                produkPtr[j] = temp;
            }
        }
        sort = true;
    }

    int binarySearch(Produk *produkPtr[], int posisi, string target) {
    int low = 0, high = posisi - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int comparison = target.compare(produkPtr[mid]->nama);
        if (comparison == 0) {
            return mid; 
        } else if (comparison < 0) {
            high = mid - 1; 
        } else {
            low = mid + 1; 
        }
    }
    return -1;
}


    int interpolationSearch(Produk *produkPtr[], int posisi, double target) {
    int low = 0, high = posisi - 1;
    while (low <= high && target >= produkPtr[low]->pembeli.number && target <= produkPtr[high]->pembeli.number) {
        int pos = low + ((target - produkPtr[low]->pembeli.number) * (high - low)) / (produkPtr[high]->pembeli.number - produkPtr[low]->pembeli.number);
        if (produkPtr[pos]->pembeli.number == target) {
            return pos;
        } else if (produkPtr[pos]->pembeli.number < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    return -1;
}

    void menu(Produk *produkPtr[], int &posisi) {
        int pilih;
        string ulang;
        Produk produk;
        do {
            system("cls");
            cout << "\nAyo pilih\n";
            cout << "1. Tampilkan data produk investasi\n";
            cout << "2. Tambahkan data produk investasi\n";
            cout << "3. Perbarui informasi produk investasi\n";
            cout << "4. Hapus data produk investasi\n";
            cout << "5. Sorting\n";
            cout << "6. Searching\n";
            cout << "7. Selesai\n";
            cout << "Tentukan Pilihan anda: ";
            cin >> pilih;

            switch (pilih) {
                case 1:
                    produk.tampilkan(produkPtr, posisi);
                    break;
                case 2:
                    produk.tambahdata(produkPtr, posisi);
                    break;
                case 3:
                    produk.perbarui(produkPtr, posisi);
                    break;
                case 4:
                    produk.hapusdata(produkPtr, posisi);
                    break;
                case 5:
                    system("cls");
                    cout << "Pilihan sorting:" << endl;
                    cout << "1. Bubble Sort (Ascending)" << endl;
                    cout << "2. Quick Sort (Descending)" << endl;
                    cout << "3. Shell Sort (Ascending)" << endl;
                    cout << "Tentukan Pilihan sorting anda: ";
                    cin >> pilih;
                    switch (pilih) {
                        case 1:
                            produk.bubbleSortAscending(produkPtr, posisi);
                            cout << "Sorting berhasil (Bubble Sort - Ascending)" << endl;
                            tampilkan(produkPtr, posisi);
                            break;
                        case 2:
                            produk.quickSortDescending(produkPtr, 0, posisi - 1);
                            cout << "Sorting berhasil (Quick Sort - Descending)" << endl;
                            tampilkan(produkPtr, posisi);
                            break;
                        case 3:
                            produk.shellSortAscending(produkPtr, posisi);
                            cout << "Sorting berhasil (Shell Sort - Ascending)" << endl;
                            tampilkan(produkPtr, posisi);
                            break;
                        default:
                            cout << "Pilihan sorting tidak valid" << endl;
                            break;
                    }
                    break;
                case 6:
                    system("cls");
                    cout << "Pilihan searching:" << endl;
                    cout << "1. Binary Search" << endl;
                    cout << "2. Interpolation Search" << endl;
                    cout << "Tentukan Pilihan searching anda: ";
                    cin >> pilih;
                    switch (pilih) {
                        case 1: {
                            string target;
                            cout << "Masukkan nama yang ingin dicari: ";
                            cin >> target;
                            int result = produk.binarySearch(produkPtr, posisi, target);
                            if (result != -1) {
                                cout << "Data ditemukan pada posisi: " << result + 1 << endl;
                            } else {
                                cout << "Data tidak ditemukan" << endl;
                            }
                            break;
                        }
                        case 2: {
                            double target;
                            cout << "Masukkan nomor telfon yang ingin dicari: ";
                            cin >> target;
                            int result = produk.interpolationSearch(produkPtr, posisi, target);
                            if (result != -1) {
                                cout << "Data ditemukan pada posisi: " << result + 1 << endl;
                            } else {
                                cout << "Data tidak ditemukan" << endl;
                            }
                            break;
                        }
                        default:
                            cout << "Pilihan searching tidak valid" << endl;
                            break;
                    }
                    break;
                case 7:
                    cout << "Anda telah keluar dari program\n";
                    break;
                default:
                    cout << "Pilih angka 1-7" << endl;
                    break;
            }
            if (pilih == 7) {
                break;
            }
            cout << "Kembali ke menu? (y/n): ";
            cin >> ulang;
        } while (ulang == "y" || ulang == "Y");
    }
};

int main() {
    try {
        Produk produk;
        Produk *produkPtr[max_produk];
        int posisi = 0;

        int i;
        string pass_input, user_input;
        cout << "=====================================================\n";
        cout << "                   AYO INVESTASI!!!\n";
        cout << "=====================================================\n";
        cout << "Investasikan hari ini, raih impian masa depanmu.\n";
        cout << "=====================================================\n\n";
        string username = "oktaria";
        string password = "2309106015";
        string login = "block";
        i = 1;

        do {
            cout << "Username = ";
            cin >> user_input;
            cout << "Password = ";
            cin >> pass_input;
            if (user_input == username && pass_input == password) {
                cout << " =====================================\n";
                cout << "| Login Berhasil Selamat berinvestasi |" << endl;
                i = 4;
                login = "berhasil";
            } else {
                cout << "\n=============================\n";
                cout << "Username / Password Salah!!! (" << i << "x)\n";
                cout << "=============================\n\n";
                i = i + 1;
            }
        } while (i <= 3 && login != "berhasil");

        if (login != "berhasil") {
            cout << "Anda telah 3x salah login.\n";
            cout << "Silahkan coba setelah 24 jam dari sekarang. Terima Kasih..\n\n";
            return 0;
        }

        produk.menu(produkPtr, posisi);
        cout << "Buatlah langkah kecil menuju kebebasan finansial dengan investasi.. Sampai jumpa lagi ";
        return 0;
    } catch (...) {
        cerr << "Terjadi kesalahan yang tidak terduga. Program berhenti." << endl;
    }
    return 0;
}
