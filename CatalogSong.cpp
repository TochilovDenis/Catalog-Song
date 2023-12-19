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
			cout << "1. Добавить песню\n"
				<< "2. Удалить песню\n"
				<< "3. Изменить песню\n"
				<< "4. Показать песню\n"
				<< "5. Поиск по автору\n"
				<< "6. Поиск по тексту песни\n"
				<< "7. Загрузить песни из файла\n"
				<< "8. Сохранить песни в файл\n"
				<< "9. Выход\n"
				<< "Выберите действие: ";
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
				cout << "Введите название песни для отображения: ";
				getline(cin, title);
				displaySong(title);
				break;
			case 5:
				cout << "Введите имя автора для поиска песен: ";
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
		cout << "Введите название песни: ";
		getline(cin, newSong.title);
		cout << "Введите автора песни: ";
		cin >> newSong.author;
		cout << "Введите год выпуска песни: ";
		cin >> newSong.year;
		cout << "Введите текст песни (введите 'END' в новой строке, когда закончите):\n";
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
			cout << "Песня удалена.\n";
		}
		else {
			cout << "Песня не найдена.\n";
		}
	}

	void removeSongInteractive() {
		string title;
		cout << "Введите название песни для удаления: ";
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
		(songUpdated) ? cout << "Песня изменена.\n" : cout << "Песня не найдена.\n";
	}

	void updateSongInteractive() {
		cout << "Введите название песни для обновления: ";
		cin.ignore();
		string title;
		getline(cin, title);
		Song newSong;
		cout << "Введите новые данные песни.\n";
		cout << "Название: ";
		getline(cin, newSong.title);
		cout << "Автор: ";
		getline(cin, newSong.author);
		cout << "Год: ";
		cin >> newSong.year;
		cin.ignore();
		cout << "Текст: ";
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
			cout << "Песня не найдена.\n";
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
			cout << "Песни этого автора не найдены.\n";
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