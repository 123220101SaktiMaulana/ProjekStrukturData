#include <iostream>
#include <cstring>

// Anggota Kelompok : 
// Baiq Afifah Hanum / 123220037
// Sakti Maulana Ibrahim / 123220101
// Faiza Nur Rafida  / 123220159


// nomor buku menggunakan integer pastikan input dengan angka
// pilihan menu menggunakan integer pastikan input dengan angka

using namespace std;

struct Data
{
    char judul[50];
    char penulis[50];
    int nomor;
    Data *kanan = NULL;
    Data *kiri = NULL;
    Data *next = NULL;
};

Data *akar = NULL;
Data *bantu;
Data *help;
Data *tabelHash[10];

char judulbaru[50];
char penulisbaru[50];
int nomorbaru;

Data *akarsampah;
Data *bantusampah;
Data *helpsampah;

bool kosong()
{
    if (akar == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool kosong2()
{
    if (akarsampah == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void archive(char a[50],char b[50], int c)
{

    Data *NBS = new Data();

    strcpy(NBS->judul,a);
    strcpy(NBS->penulis,b);
    NBS->nomor = c;
    NBS->kanan = NULL;
    NBS->kiri = NULL;

    // cout << b;

    if (kosong2())
    {
        akarsampah = NBS;
        // cout << "first " << endl;
    }
    else
    {
        helpsampah = akarsampah;
        bantusampah = akarsampah;
        while (helpsampah != NULL && strcmp(bantusampah->judul, a) != 0)
        {
            bantusampah = helpsampah;
            if (strcmp(a,helpsampah->judul ) > 0)
            {
                helpsampah = helpsampah->kanan;
            }
            else
            {
                helpsampah = helpsampah->kiri;
            }
        }
        if (strcmp(a,bantusampah->judul) == 0)
        {
            cout << " Data sampah sudah ada jadi tidak dimasukkan" << endl;
        }
        else if (strcmp(a,bantusampah->judul) > 0)
        {
            bantusampah->kanan = NBS;
            // cout << "geser kanan " << endl;
        }
        else
        {
            bantusampah->kiri = NBS;
            // cout << "geser kiri" << endl;
        }
    }
}

int fungsiHash(int nomor)
{
    return nomor % 10;
}

void inputHash(int hashKey, Data *NB)
{
    if (tabelHash[hashKey] == NULL)
    {
        tabelHash[hashKey] = NB;
    }
    else
    {
        bantu = tabelHash[hashKey];
        while (bantu->next != NULL && bantu->next->nomor <= NB->nomor)
        {
            bantu = bantu->next;
        }

        if (bantu->next == NULL)
        {
            bantu->next = NB;
        }
        else
        {
            help = bantu->next;
            NB->next = help;
            bantu->next = NB;
        }
    }
}

void PTB(Data *NB)
{

    int hashKey = fungsiHash(NB->nomor);

    if (kosong())
    {
        akar = NB;
        inputHash(hashKey, NB);
    }
    else
    {
        help = akar;
        bantu = akar;
        while (help != NULL && strcmp(NB->judul, bantu->judul) != 0)
        {
            bantu = help;
            if (strcmp(NB->judul, bantu->judul) > 0)
            {
                help = help->kanan;
            }
            else
            {
                help = help->kiri;
            }
        }
        if (strcmp(NB->judul, bantu->judul) == 0)
        {
            cout << " Data Sudah Ada " << endl;
        }
        else if (strcmp(NB->judul, bantu->judul) > 0)
        {
            bantu->kanan = NB;
            inputHash(hashKey, NB);
            // cout << " geser kanan " << endl;
        }
        else
        {
            bantu->kiri = NB;
            inputHash(hashKey, NB);
            // cout << " geser kiri" << endl;
        }
    }
}

void tambah(char a[50], char b[50], int c)
{
    // cout << a;
    // cout << b;
    // cout << c;
    Data *NB = new Data();
    strcpy(NB->judul, a);
    strcpy(NB->penulis, b);
    NB->nomor = c;
    NB->kanan = NULL;
    NB->kiri = NULL;

    PTB(NB);
}

void TampilHash()
{
    for (int i = 0; i < 10; i++)
    {
		int no = 1;
		
        if (tabelHash[i] != NULL)
        {
            cout << " Hash[" << i << "] : " << endl;
            bantu = tabelHash[i];
            
            while (bantu != NULL)
            {
                cout << " > Buku " << no << endl;
                cout << "   Judul buku   : " << bantu->judul << endl;
                cout << "   Penulis      : " << bantu->penulis << endl;
                cout << "   No Referensi : " << bantu->nomor << endl << endl;

                bantu = bantu->next;
                no++;
            }
            
        }
    }
}

void InOrder(Data *root)
{
    if (root == NULL)
    {
        return;
    }
    
    InOrder(root->kiri);
    cout << "   Judul buku   : " << root->judul << endl;
    cout << "   Penulis      : " << root->penulis << endl;
    cout << "   No Referensi : " << root->nomor << endl << endl;
    InOrder(root->kanan);
}

void Preorder(Data *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << "   Judul buku   : " << root->judul << endl;
    cout << "   Penulis      : " << root->penulis << endl;
    cout << "   No Referensi : " << root->nomor << endl << endl;
    Preorder(root->kiri);
    Preorder(root->kanan);
}

void Postorder(Data *root)
{
    if (root == NULL)
    {
        return;
    }
    Postorder(root->kiri);
    Postorder(root->kanan);
    cout << "   Judul buku   : " << root->judul << endl;
    cout << "   Penulis      : " << root->penulis << endl;
    cout << "   No Referensi : " << root->nomor << endl << endl;
}

Data *deleteHash(Data *atas, int index, char namahapus[50])
{
    if (atas == NULL)
        return NULL;

    if (strcmp(atas->judul, namahapus) == 0)
    {
        atas = deleteHash(atas->next, index, namahapus);
    }
    else
    {
        atas->next = deleteHash(atas->next, index, namahapus);
    }
    return atas;
}

void hapusPTB()
{
    Data *temp;
    if (help->kiri == NULL && help->kanan == NULL)
    {
        if (bantu == akar && help == akar)
        {
            akar = NULL;
            // cout << "Akar " << endl;
        }
        else
        {
            if (help == bantu->kiri)
            {
                bantu->kiri = NULL;
            }
            else
            {
                bantu->kanan = NULL;
            }
            // cout << "Hapus daun " << endl;
        }
        archive(help->judul, help->penulis, help->nomor);
        cout << " Buku dengan judul '" << help->judul << "' telah dihapus " << endl;
        delete help;
        // cout << "Daun " << endl;
    }
    else if (help->kiri != NULL && help->kanan != NULL)
    {
        temp = help->kiri;
        bantu = help;
        while (temp->kanan != NULL)
        {
            bantu = temp;
            temp = temp->kanan;
        }
        archive(help->judul, help->penulis, help->nomor);

        cout << " Buku dengan judul '" << help->judul << "' telah dihapus " << endl;

        strcpy(help->judul, temp->judul);
        strcpy(help->penulis, temp->penulis);
        help->nomor = temp->nomor;

        if (bantu == help){
            if(temp->kanan != NULL){
                help->kiri = temp->kanan;
            }else{
                help->kiri = NULL;
            }
        }else{
            if(temp->kanan != NULL){
                bantu->kanan = temp->kanan;
            }else{
                bantu->kanan = NULL;
            }
        }
        temp->kanan = NULL;
        temp->kiri = NULL;

        // cout << "Hapus node yg mempunyai daun " << endl;
    }
    else if (help->kiri != NULL && help->kanan == NULL)
    {
        if (bantu == help)
        {
            akar = help->kiri;
        }
        else
        {
            if (help == bantu->kiri)
            {
                bantu->kiri = help->kiri;
            }
            else
            {
                bantu->kanan = help->kiri;
            }
        }
        archive(help->judul, help->penulis, help->nomor);

        cout << " Buku dengan judul '" << help->judul << "' telah dihapus " << endl;

        delete help;
        // cout << "Hapus Node yang tidak mempunyai anak kanan " << endl;
    }
    else if (help->kiri == NULL && help->kanan != NULL)
    {
        if (bantu == help)
        {
            akar = help->kanan;
        }
        else
        {
            if (help == bantu->kanan)
            {
                bantu->kanan = help->kanan;
            }
            else
            {
                bantu->kiri = help->kanan;
            }
        }
        archive(help->judul, help->penulis, help->nomor);

        cout << " Buku dengan judul '" << help->judul << "' telah di hapus " << endl;

        delete help;
        // cout << "Hapus Node yang tidak mempunyai anak kiri " << endl;
    }
}

void hapusdata()
{
    char hapus[50];
    
    if (kosong())
    {
        cout << " Data masih kosong! " << endl;
        return;
    }
    else
    {

        cout << " Masukkan judul buku yang ingin dihapus : ";
        cin.getline(hapus, sizeof(hapus));

        for (int i = 0; i < 10; ++i)
        {
            if (tabelHash[i] != NULL)
            {
                tabelHash[i] = deleteHash(tabelHash[i], i, hapus);
            }
        }

        bantu = akar;
        help = akar;


        while (help != NULL && strcmp(hapus, help->judul) != 0)
        {
            bantu = help;
            if (strcmp(hapus, help->judul) < 0)
            {
                help = bantu->kiri;
            }
            else
            {
                help = bantu->kanan;
            }
        }
        if (help == NULL)
        {
            cout << " Judul buku yang ingin dihapus tidak ada " << endl;
            return;
        }
    }
    hapusPTB();
}

void carinomor(){
    int carino;

    cout << " Masukkan nomor referensi buku yang ingin dicari : ";
    cin >> carino;

    int index = fungsiHash(carino);
    bool ketemu = false;

    if (tabelHash[index] != NULL){
        bantu = tabelHash[index];

        while (bantu != NULL){
            if (bantu->nomor == carino){
                ketemu = true;
                cout << endl;
                cout << " Judul buku   : " << bantu->judul << endl;
                cout << " Penulis      : " << bantu->penulis << endl;
                cout << " No Referensi : " << bantu->nomor << endl << endl;
            }
            
            bantu = bantu->next;
        }
    }

    if (!ketemu){
        cout << " Buku tidak ada " << endl;
    }
}

void carijudul(Data *root,char awal[5],char akhir[5]){
    if (root == NULL) {
        return;
    }
    carijudul(root->kiri, awal, akhir);

    if (root->judul[0] >= awal[0] && root->judul[0] <= akhir[0]){
        cout << "   Judul buku   : " << root->judul << endl;
        cout << "   Penulis      : " << root->penulis << endl;
        cout << "   No Referensi : " << root->nomor << endl << endl;
    }
    carijudul(root->kanan, awal, akhir);
}

void Sampah()
{
    int pil2;
    cout << " Data Sampah(urutan)    							" << endl;
    cout << " [1] PreOrder 				   						" << endl;
    cout << " [2] InOrder 				   						" << endl;
    cout << " [3] PostOrder                 						" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " Masukkan urutan yang dipilih : ";
    cin >> pil2;
    switch (pil2)
    {
    case 1:
        system("cls");
        
        cout << " ~~~~ Data Archive(PreOrder) ~~~~" << endl << endl;
        Preorder(akarsampah);
        if (kosong2())
        {
            cout << " Data masih kosong !" << endl;
        }
        cout << endl;
        break;

    case 2:
        system("cls");

        cout << " ~~~~ Data Archive(InOrder) ~~~~" << endl << endl;
        InOrder(akarsampah);
        if (kosong2())
        {
            cout << "\n Data masih kosong !" << endl;
        }
        cout << endl;
        break;

    case 3:
        system("cls");

        cout << " ~~~~ Data Archive(PostOrder) ~~~~" << endl << endl;
        Postorder(akarsampah);
        if (kosong2())
        {
            cout << "\n Data masih kosong !" << endl;
        }
        cout << endl;
        break;

    default:
        cout << " Masukkan pilihan yang benar " << endl;
        break;
    }
}

int main()
{
    int pil;
    char ulang;
    do
    {
        system("cls");
        cout << "\n";

		cout << "   	          ~~~~~~ kel(037, 101, 159) ~~~~~~ 				    " << endl; 
		cout << "      	        ~~ S E L A M A T   D A T A N G ~~					" << endl; 	
		cout << "    	    ~~~~~~~~~~ PROGRAM PERPUSTAKAAN ~~~~~~~~~				" << endl; 
        cout << "===================================================================" << endl;
        cout << "|                         MENU UTAMA                              |" << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "| [1] Tambah Buku                                                 |" << endl;
        cout << "| [2] Lihat Buku (Menggunakan Hash)                               |" << endl;
        cout << "| [3] Lihat Buku (Menggunakan PTB Ascending)                      |" << endl;
        cout << "| [4] Hapus Buku                                                  |" << endl;
        cout << "| [5] Cari Buku (Berdasarkan Nomor Buku)                          |" << endl;
        cout << "| [6] Cari Buku (Berdasarkan Judul Buku) masukkan rentan a - z    |" << endl;
        cout << "| [7] History Buku                                                |" << endl;
        cout << "| [8] Exit                                                        |" << endl;
		cout << "===================================================================" << endl;
        cout << " Masukkan Pilihan Menu : ";
        cin >> pil;
        cin.ignore();
        switch (pil)
        {
        case 1:
			system("cls");
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
            cout << "\n        TAMBAH DATA 		     ";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
            cout << endl << endl;
            cout << " Masukkan Nama Buku\t: ";
            cin.getline(judulbaru, 50);
            cout << " Masukkan Penulis Buku\t: ";
            cin.getline(penulisbaru, 50);
            cout << " Masukkan Nomor Buku\t: ";
            cin >> nomorbaru;
            tambah(judulbaru, penulisbaru, nomorbaru);

            break;

        case 2:
			system("cls");
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
            cout << "\n     LIHAT DATA (Hash)        ";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			cout << endl << endl; 
            TampilHash();
            break;

        case 3:
			system("cls");
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
            cout << "\n       LIHAT DATA (PTB)       ";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
            cout << endl << endl;
            InOrder(akar);
            break;

        case 4:
			system("cls");
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
            cout << "\n       HAPUS DATA BUKU        ";
           	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
           	cout << endl << endl;    
            TampilHash();
            hapusdata();

            break;

        case 5:
			system("cls");
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
            cout << "\n     CARI BUKU BERDASARKAN NOMOR REFERENSI  		  ";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
            cout << endl << endl;
            TampilHash();
            carinomor();

            break;

        case 6:
			system("cls");
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
			cout << "\n        CARI BUKU BERDASARKAN RENTAN (a-z)		  ";
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
			cout << endl << endl;
            TampilHash();
            char bawah[5],atas[5];
            cout << " Batas huruf atas\t: ";
            cin.getline(bawah, sizeof(bawah));
            cout << " Batas huruf bawah \t: ";
            cin.getline(atas, sizeof(atas));

            carijudul(akar, bawah, atas);
            cout << endl;

            break;

        case 7:
			system("cls");
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
			cout << "\n         HISTORY(Data Buku yang Dihapus)	          ";
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"; 
			cout << endl;
            Sampah();
            break;
            
        case 8:
			exit(0);
            break;
            
        default:
            cout << " Nomor yang anda pilih tidak tersedia " << endl;
            break;
        }
        cout << "\n Kembali ke Menu? y/n : ";
        cin >> ulang;
    } while (ulang == 'y');
}
