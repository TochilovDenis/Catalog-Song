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