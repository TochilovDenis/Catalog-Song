#include <iostream>
#include <vector>

using namespace std;

struct Song
{
	string title, author, year, lyrics;
};

struct CatalogSong{
	vector<Song> songs;
	
	void DisplayMenu() {
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
			default:
				break;
			}
		} while (true);
	}

	void addSong(const Song& song) {
		songs.push_back(song);
	}

};

int main(){
	setlocale(LC_ALL,"");

	return 0;
}