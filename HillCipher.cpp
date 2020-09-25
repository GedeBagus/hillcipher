/*
Shania Salsabila, M. ilham habib, Gede Bagus D
140810180014, 140810180018, 140810180068
Hill Cipher
*/

#include <iostream>
using namespace std;

class HillCipher
{
private:
	// operasi mod
	int mod(int a, int b)
	{
		int c = a % b;
		return (c < 0) ? c + b : c;
	}
	//menghitung gcd
	int gcd(int a, int b)
	{
		if (b == 0)
			return a;
		else
			return gcd(b, a % b);
	}

	// menghitung multiplicative inverse b  mod a
	int computeInverse(int a, int b)
	{
		int n = a;
		int old_x = 1, x = 0;
		int old_y = 0, y = 1;
		int q, r;
		while (b != 0)
		{
			q = a / b; 
			r = a % b; 
			int temp = x;
			x = old_x - q * x;
			old_x = temp;
			temp = y;
			y = old_y - q * y;
			old_y = temp;
			a = b;
			b = r;
		}
		int inverse = mod(old_y, n);
		return inverse;
	}

public:
	int key[2][2];
	// mengambil key
	void getKey()
	{
		cout << "Masukkan 4 elemen kunci matriks 2*2 :\n";
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cin >> key[i][j];
			}
		}
	}
	//mengecek kevalidan key
	bool isValid(int a[2][2])
	{
		int d = a[0][0] * a[1][1] - a[1][0] * a[0][1];
		d = mod(d, 26);
		return (gcd(d, 26) == 1) && d != 0 ? true : false;
	}
	string getMessage()
	{
		string msg;
		cout << "Masukkan Message: ";
		cin >> msg;

		for (int i = 0; i < msg.length(); i++)
		{
			msg[i] = toupper(msg[i]);
		}
		if (msg.length() % 2 != 0)
		{
			msg += "0";
		}
		return msg;
	}
	// fungsi enkripsi
	void encrypt(string msg)
	{
		cout << "Key dari matrix : \n";
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
				cout << key[i][j] << " ";
			cout << endl;
		}
		string cipherText = "";
		int row = msg.length() / 2;
		int msg2D[row][2];
		int p = 0;
		do
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					msg2D[i][j] = msg[p] - 'A';
					p++;
				}
			}
		} while (p < msg.length());

		//	pengecekan matrix
		cout << "Matriks dari message tadi : " << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << msg2D[i][j] << " ";
			}
			cout << endl;
		}
		cout << "------------------------------ " << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << (char)(msg2D[i][j] + 'A') << " ";
			}
			cout << endl;
		}
		//mengalikan message matrix dengan key matrix
		int mult[row][2];
		int i, j, k, sum = 0;
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < 2; j++)
			{
				for (k = 0; k < 2; k++)
				{
					sum = sum + msg2D[i][k] * key[k][j];
				}
				mult[i][j] = mod(sum, 26);
				sum = 0;
			}
		}

		cout << "Setelah di enkripsi hasilnya adalah : \n ";
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < 2; j++)
				cout << mult[i][j] << " ";
			cout << " \n";
		}
		//membuat cipherText
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				char c = toupper(mult[i][j] + 'A');
				cipherText.push_back(c);
			}
		}
		cout << "CipherText : " << cipherText;
	}
	// fungsi dekripsi
	void decryption(string msg)
	{
		string plainText = "";
		int row = msg.length() / 2;
		int msg2D[row][2];
		int p = 0;
		do
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					msg2D[i][j] = msg[p] - 'A';
					p++;
				}
			}
		} while (p < msg.length());
		cout << "Matrix dari message diatas :" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << msg2D[i][j] << " ";
			}
			cout << endl;
		}
		cout << "------------------------------ " << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << (char)(msg2D[i][j] + 'A') << " ";
			}
			cout << endl;
		}
		//menghitung determinan
		int d = key[0][0] * key[1][1] - key[0][1] * key[1][0];
		d = mod(d, 26);
		cout << "det= " << d << "\t";
		//menghitung 1/det mod 26
		int oneByDet = computeInverse(26, d);
		cout << "1/det= " << oneByDet << "\n";
		//menghitung inverse key

		int keyInvrs[row][2];
		keyInvrs[0][0] = mod(oneByDet * key[1][1], 26);
		keyInvrs[1][1] = mod(oneByDet * key[0][0], 26);
		keyInvrs[0][1] = mod(oneByDet * -1 * key[0][1], 26);
		keyInvrs[1][0] = mod(oneByDet * -1 * key[1][0], 26);
		cout << "The inverse key matrix is : \n";
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
				cout << keyInvrs[i][j] << " ";
			cout << endl;
		}
		int mult[row][2];
		int i, j, k, sum = 0;
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < 2; j++)
			{
				for (k = 0; k < 2; k++)
				{
					sum = sum + msg2D[i][k] * keyInvrs[k][j];
				}
				mult[i][j] = mod(sum, 26);
				sum = 0;
			}
		}
		cout << "Hasil Dekripsi \n ";
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < 2; j++)
				cout << mult[i][j] << " ";
			cout << " \n ";
		}
		//membuat plaintText
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				char c = toupper(mult[i][j] + 'A');
				plainText.push_back(c);
			}
		}
		cout << "Plain Text : " << plainText;
	}
};
int main()
{
	cout << "HILL CIPHER" << endl
		 << endl;
	HillCipher hc;
	string message;
	int choice;
	char more = 'y';
	cout << "MENU" << endl
		 << endl;
	while (more == 'y')
	{

		cout << " 1. Enkripsi " << endl;
		cout << " 2. Dekripsi " << endl;
		cout << " 3. Exit " << endl;
		cout << "Masukkan pilihan : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			hc.getKey();
			if (hc.isValid(hc.key))
			{
				cout << "Key yang dimasukkan valid\n";
			}
			else
			{
				cout << "Key yang dimasukkan tidak valid\n";
				exit(0);
			}
			message = hc.getMessage();
			hc.encrypt(message);
			break;
		case 2:
			hc.getKey();
			if (hc.isValid(hc.key))
			{
				cout << "Key yang dimasukkan valid\n";
			}
			else
			{
				cout << "Key yang dimasukkan tidak valid\n";
				exit(0);
			}
			message = hc.getMessage();
			hc.decryption(message);
			break;
		case 3:
			exit(0);
		default:
			cout << "Pilihan salah!!" << endl;
		}
		cout << "\n\nTekan y jika ingin melanjutkan program" << endl;
		cin >> more;
	}
	return 0;
}
