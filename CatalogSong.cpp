#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Song
{
	string title, author, year, lyrics;
};

struct CatalogSong {
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
			string title, author;
			switch (choice)
			{
			case 1:
				addSongInteractive(catalog);
				break;
			case 2:
				removeSongInteractive();
				break;
			case 3:
				updateSongInteractive();
				break;
			case 4:
				cout << "������� �������� ����� ��� �����������: ";
				getline(cin, title);
				displaySong(title);
				break;
			case 5:
				cout << "������� ��� ������ ��� ������ �����: ";
				cin.ignore();
				getline(cin, author);
				searchByAuthor(author);
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

	void removeSong(const string& title) {
		auto it = remove_if(songs.begin(), songs.end(), [&](const Song& s) {
			return s.title == title;
			});
		if (it != songs.end()) {
			songs.erase(it, songs.end());
			cout << "����� �������.\n";
		}
		else {
			cout << "����� �� �������.\n";
		}
	}

	void removeSongInteractive() {
		string title;
		cout << "������� �������� ����� ��� ��������: ";
		cin.ignore();
		getline(cin, title);
		removeSong(title);
	}

	void updateSong(const string& title, const Song& newSong) {
		bool songUpdated = false;
		for (Song& song : songs) {
			if (song.title == title) {
				song = newSong;
				songUpdated = true;
				break;
			}
		}
		(songUpdated) ? cout << "����� ��������.\n" : cout << "����� �� �������.\n";
	}

	void updateSongInteractive() {
		cout << "������� �������� ����� ��� ����������: ";
		cin.ignore();
		string title;
		getline(cin, title);
		Song newSong;
		cout << "������� ����� ������ �����.\n";
		cout << "��������: ";
		getline(cin, newSong.title);
		cout << "�����: ";
		getline(cin, newSong.author);
		cout << "���: ";
		cin >> newSong.year;
		cin.ignore();
		cout << "�����: ";
		getline(cin, newSong.lyrics);
		updateSong(title, newSong);
	}

	void displaySong(const string& title) {
		bool songFound = false;
		for (const Song& song : songs) {
			if (song.title == title) {
				cout << "Title: " << song.title
					<< "\nAuthor: " << song.author
					<< "\nYear: " << song.year
					<< "\nLyrics: " << song.lyrics;
				songFound = true;
				break;
			}
		}
		if (!songFound) {
			cout << "����� �� �������.\n";
		}
	}

	string toLower(const string& s) {
		string lower;
		for (char c : s) {
			lower += tolower(c);
		}
		return lower;
	}

	string toUpper(const string& s) {
		string upper;
		for (char c : s) {
			upper += toupper(c);
		}
		return upper;
	}

	string trim(const string& s) {
		string trimmed;
		for (char c : s) {
			if (!isspace(c)) {
				trimmed += c;
			}
		}
		return trimmed;
	}

	void searchByAuthor(const string& author) {
		vector<Song> results;
		string lowerAuthor = toLower(trim(author));
		string upperAuthor = toUpper(trim(author));
		for (const Song& song : songs) {
			string lowerSongAuthor = toLower(trim(song.author));
			string upperSongAuthor = toUpper(trim(song.author));
			if (lowerSongAuthor == lowerAuthor || lowerSongAuthor == upperAuthor ||
				upperSongAuthor == lowerAuthor || upperSongAuthor == upperAuthor) {
				results.push_back(song);
			}
		}
		if (results.empty()) {
			cout << "����� ����� ������ �� �������.\n";
		}
		else {
			for (const Song& song : results) {
				cout << "Title: " << song.title
					<< "\nAuthor: " << song.author
					<< "\nYear: " << song.year
					<< "\nLyrics: " << song.lyrics << "\n";
			}
		}
	}
};

int main(){
	setlocale(LC_ALL,"");
	CatalogSong catalog;
	catalog.DisplayMenu(catalog);
	return 0;
}