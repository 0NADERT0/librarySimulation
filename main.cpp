#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<math.h>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


int personID = 0;

class Book{
private:
	int idBook;
	string name;
	string author;
	int year = -1;
	vector<string> genres;

public:
	Book(int id, string name, string author, int year){
		this->idBook = id;
		this->name = name;
		this->author = author;
		this->year = year;
	}

    int getId() const { return idBook; }
    const string& getName() const { return name; }
    const string& getAuthor() const { return author; }
    int getYear() const { return year; }

    void addGenre(const string& genre) {
        genres.push_back(genre);
    }

    const vector<string>& getGenres() const { return genres; }
};


class Person{
private:
	int idPerson;
	string firstName;
	string lastName;
	int ageOfPerson;
	vector<int> booksOfPerson;

};



int main(){
	vector<Book> booksOfLibrary;
	vector<Person> clientsOfLibrary;

	ifstream file("books.json");
    
    if (!file.is_open()){
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    json j;
    file >> j;

    for (const auto& book : j){

		Book newBook = Book(book["id"], book["name"], book["author"], book["year"]);

        for (const auto& genre : book["genres"]){
			newBook.addGenre(genre);
        }

		booksOfLibrary.push_back(newBook);

    }


	cout << "Welcome to the library, what would you want?" << endl;
	cout << "1: Show all the books" << endl;
	cout << "2: Show books by genre, author, year" << endl;
	cout << "3: To take a specific book" << endl;
	cout << "4: To donate a book" << endl;
	cout << "5: To return a book" << endl;
	cout << "6: To exit the library" << endl;
	int action = 0;


	while(true){
		cin >> action;
		if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
		switch(action){
			case 1:
			{
				for (const auto& book : j){
					cout << "ID: " << book["id"] << endl;
					cout << "Название: " << book["name"] << endl;
					cout << "Автор: " << book["author"] << endl;
					cout << "Год: " << book["year"] << endl;
					cout << "Жанры: ";
					
					for (const auto& genre : book["genres"]){
						cout << genre << " ";
					}
					
					cout << endl << endl;
				}
				break;
			}
			case 2:
			{
				cout << "1: To Show books by genre" << endl;
				cout << "2: To show books by author" << endl;
				cout << "3: To show books by years" << endl;
				int choose = 0;
				cin >> choose;
				if (choose == 1){
					string genre_;
					cout << "Input prefered genre" << endl;
					cin >> genre_;
					for (char& c: genre_){
						c = tolower(c);
					}
					genre_[0] = toupper(genre_[0]);
					cout << genre_ << endl;
					for (const auto& book: booksOfLibrary){
						vector<string> now = book.getGenres();
						for (auto i: now) cout << i << " ";
						if (find(now.begin(), now.end(), genre_) != now.end()){
							cout << "ID: " << book.getId() << endl;
							cout << "Название: " << book.getName() << endl;
							cout << "Автор: " << book.getAuthor() << endl;
							cout << "Год: " << book.getYear() << endl;
							cout << "Жанры: ";
							
							for (const auto& genre : now){
								cout << genre << " ";
							}
							
							cout << endl << endl;
						}
					}
				}
				break;
			}
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				cout << "Goodbye";
				return 0;
			default:
				cout << "Don't know the command, please try again" << endl;
				break;
		}
	}
}