#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Song
{
	string title, author, year, lyrics;
};

struct CatalogSong{
	vector<Song> songs;
	
	void DisplayMenu(CatalogSong& catalog) {
		int choice;
		do
		{
			cout << "1. �������� �����\n"
				<< "2. ������� �����\n"
			    << "3. �������� �����\n"
				<< "4. �������� �����\n"
				<< "5. ����� �� ������\n"
				<< "6. ����� �� ������ �����\n"
				<< "7. ��������� ����� �� �����\n"
				<< "8. ��������� ����� � ����\n"
				<< "9. �����\n"
				<< "�������� ��������: ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				addSongInteractive(catalog);
				break;

			default:
				break;
			}
		} while (true);
	}

	void addSong(const Song& song) {
		songs.push_back(song);
	}

	void addSongInteractive(CatalogSong& catalog) {
		Song newSong;
		cout << "������� �������� �����: ";
		getline(cin, newSong.title);
		cout << "������� ������ �����: ";
		cin >> newSong.author;
		cout << "������� ��� ������� �����: ";
		cin >> newSong.year;
		cout << "������� ����� ����� (������� 'END' � ����� ������, ����� ���������):\n";
		string lyrics_line;
		while (getline(cin, lyrics_line) && lyrics_line != "END") {
			newSong.lyrics += lyrics_line + "\n";
		}
		catalog.addSong(newSong);
	}
};

int main(){
	setlocale(LC_ALL,"");

	return 0;
}