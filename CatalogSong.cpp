#include <fstream>
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
			if (cin.fail()) {
				cout << "Введенное значение не является числом. Попробуйте еще раз.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			string title, author, lyrics, filename;
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
				cin.ignore();
				getline(cin, title);
				displaySong(title);
				break;
			case 5:
				cout << "Введите имя автора для поиска песен: ";
				cin.ignore();
				getline(cin, author);
				searchByAuthor(author);
				break;
			case 6:
				cout << "Введите текст песни для поиска: ";
				cin.ignore();
				getline(cin, lyrics);
				searchByLyrics(lyrics);
				break;
			case 7:
				cout << "Введите имя файла для загрузки: ";
				cin >> filename;
				loadFromFile(filename);
				break;
			case 8:
				cout << "Введите имя файла для сохранения: ";
				cin >> filename;
				saveToFile(filename);
				break;
			case 9:
				return;
			default:
				cout << "Неверный ввод. Попробуйте еще раз.\n";
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
		cin.ignore();
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

	void searchByLyrics(const string& lyrics) {
		vector<Song> results;
		string lowerLyrics = lyrics;
		for (char& c : lowerLyrics) {
			c = tolower(c);
		}
		for (const Song& song : songs) {
			string lowerSongLyrics = song.lyrics;
			for (char& c : lowerSongLyrics) {
				c = tolower(c);
			}
			if (lowerSongLyrics.find(lowerLyrics) != string::npos) {
				results.push_back(song);
			}
		}
		if (results.empty()) {
			cout << "Песен с этими текстами не найдено.\n";
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

	void loadFromFile(const string& filename) {
		ifstream file(filename);
		if (file.is_open()) {
			Song song;
			string line;
			bool lyrics = false;
			while (getline(file, line)) {
				if (file.fail()) {
					cout << "Чтение файла не удалось.\n";
					break;
				}
				if (line == "End song") {
					if (!song.title.empty()) {
						cout << "Title: " << song.title << "\n"
							<< "Author: " << song.author << "\n"
							<< "Year: " << song.year << "\n"
							<< "Lyrics: " << song.lyrics << "\n";
						songs.push_back(song);
					}
					song.title.clear();
					song.author.clear();
					song.year.clear();
					song.lyrics.clear();
					lyrics = false;
				}
				else if (song.title.empty()) {
					song.title = line;
				}
				else if (song.author.empty()) {
					song.author = line;
				}
				else if (song.year.empty() && !line.empty()) {
					song.year = line;
				}
				else {
					song.lyrics += line + "\n";
					lyrics = true;
				}
			}
			file.close();
		}
		else {
			cout << "Не удалось открыть файл " << filename << "\n";
		}
	}

	void saveToFile(const string& filename) {
		ofstream file(filename, ios::trunc);
		if (file.is_open()) {
			for (const Song& song : songs) {
				file << song.title << "\n"
					<< song.author << "\n"
					<< song.year << "\n"
					<< song.lyrics << "\n"
					<< "End song" << "\n\n";
				if (!file) {
					cout << "Запись в файл не удалась.\n";
					break;
				}
			}
			file.close();
		}
		else {
			cout << "Не удалось открыть файл " << filename << "\n";
		}
	}
};

int main() {
	setlocale(LC_ALL, "");
	CatalogSong catalog;
	catalog.DisplayMenu(catalog);
	return 0;
}