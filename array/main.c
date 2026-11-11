
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#define MAKS_PRODUK 50
#define PANJANG_NAMA 50

// Array utama penyimpanan data produk
char namaProduk[MAKS_PRODUK][PANJANG_NAMA];
double hargaProduk[MAKS_PRODUK];
int stokProduk[MAKS_PRODUK];
long long jumlahTerjual[MAKS_PRODUK];

int totalProduk = 5;
double totalPendapatan = 0;

// =================================================
// FUNGSI INPUT ANGKA BULAT
// =================================================

int inputInteger(const char pesan[], int minimum, int maksimum) {
    char teks[100];
    char *akhir;
    long nilai;

    while (1) {
        printf("%s", pesan);

        if (fgets(teks, sizeof(teks), stdin) == NULL) {
            continue;
        }

        nilai = strtol(teks, &akhir, 10);

        while (isspace((unsigned char)*akhir)) {
            akhir++;
        }

        if (akhir == teks || *akhir != '\0' ||
            nilai < minimum || nilai > maksimum) {
            printf("Input tidak valid! Masukkan angka %d sampai %d.\n",
                   minimum, maksimum);
        } else {
            return (int)nilai;
        }
    }
}

// =================================================
// FUNGSI INPUT HARGA
// =================================================

double inputHarga(const char pesan[]) {
    char teks[100];
    char *akhir;
    double nilai;

    while (1) {
        printf("%s", pesan);

        if (fgets(teks, sizeof(teks), stdin) == NULL) {
            continue;
        }

        nilai = strtod(teks, &akhir);

        while (isspace((unsigned char)*akhir)) {
            akhir++;
        }

        if (akhir == teks || *akhir != '\0' ||
            !isfinite(nilai) || nilai < 0 ||
            nilai > 1000000000.0) {
            printf("Harga tidak valid! Masukkan harga 0 sampai 1 miliar.\n");
        } else {
            return nilai;
        }
    }
}

// =================================================
// FUNGSI MEMBANDINGKAN TEKS TANPA MEMPERHATIKAN HURUF
// BESAR DAN KECIL
// =================================================

int samaNama(const char a[], const char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (tolower((unsigned char)a[i]) !=
            tolower((unsigned char)b[i])) {
            return 0;
        }
        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

int cariBagianNama(const char teks[], const char kata[]) {
    int panjangTeks = strlen(teks);
    int panjangKata = strlen(kata);

    if (panjangKata == 0) {
        return 0;
    }

    for (int i = 0; i <= panjangTeks - panjangKata; i++) {
        int cocok = 1;

        for (int j = 0; j < panjangKata; j++) {
            if (tolower((unsigned char)teks[i + j]) !=
                tolower((unsigned char)kata[j])) {
                cocok = 0;
                break;
            }
        }

        if (cocok) {
            return 1;
        }
    }

    return 0;
}

// =================================================
// DATA AWAL PRODUK
// =================================================

void dataAwal() {
    strcpy(namaProduk[0], "Nasi Goreng");
    strcpy(namaProduk[1], "Mie Ayam");
    strcpy(namaProduk[2], "Es Teh Manis");
    strcpy(namaProduk[3], "Roti Bakar");
    strcpy(namaProduk[4], "Air Mineral");

    hargaProduk[0] = 15000;
    hargaProduk[1] = 12000;
    hargaProduk[2] = 5000;
    hargaProduk[3] = 10000;
    hargaProduk[4] = 4000;

    stokProduk[0] = 20;
    stokProduk[1] = 15;
    stokProduk[2] = 30;
    stokProduk[3] = 12;
    stokProduk[4] = 40;

    for (int i = 0; i < totalProduk; i++) {
        jumlahTerjual[i] = 0;
    }
}

// =================================================
// MENAMPILKAN DAFTAR PRODUK
// =================================================

void tampilProduk() {
    printf("\n================ DAFTAR PRODUK ================\n");

    printf("%-5s %-22s %-15s %-10s\n",
           "No", "Nama Produk", "Harga", "Stok");

    printf("------------------------------------------------\n");

    for (int i = 0; i < totalProduk; i++) {
        printf("%-5d %-22s Rp%-13.0f %-10d\n",
               i + 1,
               namaProduk[i],
               hargaProduk[i],
               stokProduk[i]);
    }

    printf("------------------------------------------------\n");
}

// =================================================
// MENAMBAHKAN PRODUK
// =================================================

void tambahProduk() {
    char namaBaru[PANJANG_NAMA];

    if (totalProduk >= MAKS_PRODUK) {
        printf("\nKapasitas produk sudah penuh!\n");
        return;
    }

    printf("\n========== TAMBAH PRODUK ==========\n");
    printf("Masukkan nama produk: ");

    if (fgets(namaBaru, sizeof(namaBaru), stdin) == NULL) {
        printf("Gagal membaca nama produk.\n");
        return;
    }

    namaBaru[strcspn(namaBaru, "\n")] = '\0';

    if (strlen(namaBaru) == 0) {
        printf("Nama produk tidak boleh kosong!\n");
        return;
    }

    for (int i = 0; i < totalProduk; i++) {
        if (samaNama(namaProduk[i], namaBaru)) {
            printf("Produk sudah terdaftar!\n");
            return;
        }
    }

    double hargaBaru = inputHarga("Masukkan harga produk: Rp");
    int stokBaru = inputInteger("Masukkan jumlah stok: ", 0, INT_MAX);

    strcpy(namaProduk[totalProduk], namaBaru);
    hargaProduk[totalProduk] = hargaBaru;
    stokProduk[totalProduk] = stokBaru;
    jumlahTerjual[totalProduk] = 0;

    totalProduk++;

    printf("Produk berhasil ditambahkan!\n");
}

// =================================================
// MENGUBAH HARGA DAN STOK
// =================================================

void ubahProduk() {
    tampilProduk();

    int nomor = inputInteger(
        "Pilih nomor produk: ", 1, totalProduk
    );

    int indeks = nomor - 1;

    printf("\nProduk yang dipilih: %s\n", namaProduk[indeks]);

    double hargaBaru = inputHarga("Masukkan harga baru: Rp");
    int stokBaru = inputInteger("Masukkan stok baru: ", 0, INT_MAX);

    hargaProduk[indeks] = hargaBaru;
    stokProduk[indeks] = stokBaru;

    printf("Data produk berhasil diperbarui!\n");
}

// =================================================
// TRANSAKSI PEMBELIAN BEBERAPA PRODUK
// =================================================

void transaksi() {
    int keranjang[MAKS_PRODUK] = {0};
    int nomor;
    int jumlah;
    int pilihan;
    double totalBelanja = 0;

    printf("\n========== TRANSAKSI PENJUALAN ==========\n");

    if (totalProduk == 0) {
        printf("Belum ada produk tersedia.\n");
        return;
    }

    do {
        tampilProduk();

        printf("\nPilih nomor produk (0 untuk selesai): ");
        nomor = inputInteger("", 0, totalProduk);

        if (nomor == 0) {
            break;
        }

        int indeks = nomor - 1;

        int tersedia = stokProduk[indeks] - keranjang[indeks];

        if (tersedia <= 0) {
            printf("Stok produk tersebut tidak tersedia!\n");
        } else {
            printf("Produk: %s\n", namaProduk[indeks]);
            printf("Stok tersedia: %d\n", tersedia);

            jumlah = inputInteger(
                "Masukkan jumlah pembelian: ", 1, tersedia
            );

            keranjang[indeks] += jumlah;

            printf("Produk berhasil dimasukkan ke keranjang.\n");
        }

        pilihan = inputInteger(
            "Tambah produk lain? (1=Ya, 0=Tidak): ", 0, 1
        );

        if (pilihan == 0) {
            break;
        }

    } while (1);

    // Menghitung total belanja
    for (int i = 0; i < totalProduk; i++) {
        totalBelanja += keranjang[i] * hargaProduk[i];
    }

    int adaPembelian = 0;

    for (int i = 0; i < totalProduk; i++) {
        if (keranjang[i] > 0) {
            adaPembelian = 1;
            break;
        }
    }

    if (!adaPembelian) {
        printf("Tidak ada transaksi yang dilakukan.\n");
        return;
    }

    printf("\n========== RINCIAN BELANJA ==========\n");

    for (int i = 0; i < totalProduk; i++) {
        if (keranjang[i] > 0) {
            printf("%-20s x %d = Rp%.0f\n",
                   namaProduk[i],
                   keranjang[i],
                   keranjang[i] * hargaProduk[i]);
        }
    }

    printf("-------------------------------------\n");
    printf("Total pembayaran: Rp%.0f\n", totalBelanja);

    pilihan = inputInteger(
        "Konfirmasi transaksi? (1=Ya, 0=Batal): ", 0, 1
    );

    if (pilihan == 1) {
        for (int i = 0; i < totalProduk; i++) {
            stokProduk[i] -= keranjang[i];
            jumlahTerjual[i] += keranjang[i];
        }

        totalPendapatan += totalBelanja;

        printf("Transaksi berhasil disimpan!\n");
    } else {
        printf("Transaksi dibatalkan. Stok tidak berubah.\n");
    }
}

// =================================================
// MENAMBAHKAN STOK
// =================================================

void tambahStok() {
    tampilProduk();

    int nomor = inputInteger(
        "Pilih nomor produk: ", 1, totalProduk
    );

    int indeks = nomor - 1;

    int tambahan = inputInteger(
        "Masukkan jumlah stok tambahan: ", 1, INT_MAX
    );

    if (tambahan > INT_MAX - stokProduk[indeks]) {
        printf("Jumlah stok melebihi batas maksimum!\n");
        return;
    }

    stokProduk[indeks] += tambahan;

    printf("Stok %s berhasil ditambahkan.\n", namaProduk[indeks]);
    printf("Stok sekarang: %d\n", stokProduk[indeks]);
}

// =================================================
// PENCARIAN PRODUK
// =================================================

void cariProduk() {
    char kata[PANJANG_NAMA];
    int ditemukan = 0;

    printf("\n========== PENCARIAN PRODUK ==========\n");
    printf("Masukkan nama produk: ");

    if (fgets(kata, sizeof(kata), stdin) == NULL) {
        return;
    }

    kata[strcspn(kata, "\n")] = '\0';

    if (strlen(kata) == 0) {
        printf("Kata pencarian tidak boleh kosong!\n");
        return;
    }

    for (int i = 0; i < totalProduk; i++) {
        if (cariBagianNama(namaProduk[i], kata)) {
            printf("\nNomor       : %d\n", i + 1);
            printf("Nama produk : %s\n", namaProduk[i]);
            printf("Harga       : Rp%.0f\n", hargaProduk[i]);
            printf("Stok        : %d\n", stokProduk[i]);

            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Produk tidak ditemukan!\n");
    }
}

// =================================================
// MENUKAR POSISI DATA PRODUK
// =================================================

void tukarProduk(int a, int b) {
    char tempNama[PANJANG_NAMA];
    double tempHarga;
    int tempStok;
    long long tempTerjual;

    strcpy(tempNama, namaProduk[a]);
    strcpy(namaProduk[a], namaProduk[b]);
    strcpy(namaProduk[b], tempNama);

    tempHarga = hargaProduk[a];
    hargaProduk[a] = hargaProduk[b];
    hargaProduk[b] = tempHarga;

    tempStok = stokProduk[a];
    stokProduk[a] = stokProduk[b];
    stokProduk[b] = tempStok;

    tempTerjual = jumlahTerjual[a];
    jumlahTerjual[a] = jumlahTerjual[b];
    jumlahTerjual[b] = tempTerjual;
}

// =================================================
// PENGURUTAN HARGA TERMURAH
// =================================================

void urutHarga() {
    for (int i = 0; i < totalProduk - 1; i++) {
        for (int j = 0; j < totalProduk - i - 1; j++) {
            if (hargaProduk[j] > hargaProduk[j + 1]) {
                tukarProduk(j, j + 1);
            }
        }
    }

    printf("\nProduk berhasil diurutkan dari harga termurah.\n");
    tampilProduk();
}

// =================================================
// PENGURUTAN PRODUK TERLARIS
// =================================================

void urutTerlaris() {
    for (int i = 0; i < totalProduk - 1; i++) {
        for (int j = 0; j < totalProduk - i - 1; j++) {
            if (jumlahTerjual[j] < jumlahTerjual[j + 1]) {
                tukarProduk(j, j + 1);
            }
        }
    }

    printf("\nProduk berhasil diurutkan berdasarkan penjualan terbanyak.\n");

    tampilProduk();
}

// =================================================
// LAPORAN PENJUALAN
// =================================================

void laporanPenjualan() {
    long long totalUnit = 0;
    long long penjualanTerbanyak = 0;
    int indeksTerlaris = -1;

    printf("\n========== LAPORAN PENJUALAN ==========\n");

    printf("%-22s %-15s\n", "Nama Produk", "Jumlah Terjual");
    printf("---------------------------------------\n");

    for (int i = 0; i < totalProduk; i++) {
        printf("%-22s %-15lld\n",
               namaProduk[i], jumlahTerjual[i]);

        totalUnit += jumlahTerjual[i];

        if (jumlahTerjual[i] > penjualanTerbanyak) {
            penjualanTerbanyak = jumlahTerjual[i];
            indeksTerlaris = i;
        }
    }

    printf("---------------------------------------\n");
    printf("Total barang terjual : %lld\n", totalUnit);
    printf("Total pendapatan     : Rp%.0f\n", totalPendapatan);

    if (indeksTerlaris >= 0) {
        printf("Produk paling laris  : %s\n",
               namaProduk[indeksTerlaris]);
    } else {
        printf("Produk paling laris  : Belum ada penjualan\n");
    }
}

// =================================================
// PEMERIKSAAN STOK MENIPIS
// =================================================

void cekStokMenipis() {
    int ditemukan = 0;

    printf("\n========== PERINGATAN STOK MENIPIS ==========\n");

    for (int i = 0; i < totalProduk; i++) {
        if (stokProduk[i] < 5) {
            printf("Nama produk: %-20s Stok: %d\n",
                   namaProduk[i], stokProduk[i]);

            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Semua stok produk masih mencukupi.\n");
    }
}

// =================================================
// MENU UTAMA PROGRAM
// =================================================

int main() {
    int pilihan;

    dataAwal();

    do {
        printf("\n");
        printf("====================================================\n");
        printf("     SISTEM MONITORING STOK DAN PENJUALAN KANTIN\n");
        printf("====================================================\n");
        printf("1.  Menampilkan daftar produk\n");
        printf("2.  Menambahkan produk baru\n");
        printf("3.  Mengubah harga dan stok produk\n");
        printf("4.  Melakukan transaksi pembelian\n");
        printf("5.  Menambahkan stok produk\n");
        printf("6.  Mencari produk\n");
        printf("7.  Mengurutkan harga termurah\n");
        printf("8.  Mengurutkan produk terlaris\n");
        printf("9.  Menampilkan laporan penjualan\n");
        printf("10. Memeriksa stok menipis\n");
        printf("0.  Keluar dari program\n");
        printf("====================================================\n");

        pilihan = inputInteger("Masukkan pilihan menu: ", 0, 10);

        switch (pilihan) {
            case 1:
                tampilProduk();
                break;

            case 2:
                tambahProduk();
                break;

            case 3:
                ubahProduk();
                break;

            case 4:
                transaksi();
                break;

            case 5:
                tambahStok();
                break;

            case 6:
                cariProduk();
                break;

            case 7:
                urutHarga();
                break;

            case 8:
                urutTerlaris();
                break;

            case 9:
                laporanPenjualan();
                break;

            case 10:
                cekStokMenipis();
                break;

            case 0:
                printf("\nTerima kasih telah menggunakan program!\n");
                break;
        }

    } while (pilihan != 0);

    return 0;
}
