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
};

int main(){
	setlocale(LC_ALL,"");

	return 0;
}