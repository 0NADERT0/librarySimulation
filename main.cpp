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
int mxID = 0;

class Book{
private:
	int idBook;
	string name;
	string author;
	int year = -1;
	bool available = true;
	vector<string> genres;

public:

	Book(){}

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
	bool getAvailability() const { return available; }
	void changeAvailable(){
		if (available) available = false;
		else available = true;
	}

    void addGenre(const string& genre) {
        genres.push_back(genre);
    }

	void showBook(){
		cout << "ID: " << idBook << endl;
		cout << "Name: " << name << endl;
		cout << "Author: " << author << endl;
		cout << "Year: " << year << endl;
		cout << "Available: " << available << endl;
		cout << "Genres: ";
					
		for (const auto& genre : genres){
			cout << genre << " ";
		}
					
		cout << endl << endl;
	}

    const vector<string>& getGenres() const { return genres; }
};


class Person{
private:
	int idPerson;
	string firstName;
	string lastName;
	int ageOfPerson;
	vector<Book> booksOfPerson;

public:

	Person(){}

	Person(int id, string firstName, string lastName, int age){
		idPerson = id;
		this->firstName = firstName;
		this->lastName = lastName;
		ageOfPerson = age;
	}

	int getId() const { return idPerson; }

	void showPerson(){
		cout << "idPerson: " << idPerson << endl;
		cout << "Name: " << firstName << " " << lastName << endl;
		cout << "Age: " << ageOfPerson << endl;
		cout << "booksId: ";
		for (auto& book : booksOfPerson){
			cout << book.getId() << " ";
		}
		cout << endl;
	}

	void addBook(const Book& book){
		booksOfPerson.push_back(book);
	}
};



int main(){
	vector<Book> booksOfLibrary;
	vector<Person> clientsOfLibrary;

	ifstream file("books.json");
    
    if (!file.is_open()){
        cerr << "Couldn't open file" << endl;
        return 1;
    }

    json j;
    file >> j;

    for (const auto& book : j){

		Book newBook = Book(book["id"], book["name"], book["author"], book["year"]);
		mxID = max(mxID, newBook.getId());

        for (const auto& genre : book["genres"]){
			newBook.addGenre(genre);
        }

		booksOfLibrary.push_back(newBook);

    }


	cout << "Welcome to the library, what would you want?" << endl;
	int action = 0;


	while(true){
		cout << "1: Show all the books" << endl;
		cout << "2: Show books by genre, author, year" << endl;
		cout << "3: Show all the clients" << endl;
		cout << "4: To donate a book" << endl;
		cout << "5: To return a book" << endl;
		cout << "6: To exit the library" << endl;
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
				for (auto& book : booksOfLibrary){
					book.showBook();
				}
				int takeBook = 0;
				cout << "If you want to take any book, input it's id. If you don't, input -1" << endl;
				cin >> takeBook;
				Book temp;
				if (takeBook != -1){
					if (cin.fail() || takeBook < 0 || takeBook > mxID){
            			cin.clear();
            			cin.ignore(numeric_limits<streamsize>::max(), '\n');
            			cout << "Invalid input. Please try again." << endl;
            			break;
        			}
					else{
						bool available = true;
						for (const auto& book: booksOfLibrary){
							if (book.getId() == takeBook){
								if (book.getAvailability() == false){
									available = false;
								}
								temp = book;
								break;
							}
						}
						if (!available){
							cout << "Book is not available" << endl;
							break;
						}
						int myId;
						cout << "If you have been here before, input your id, else input -1" << endl;
						cin >> myId;
						bool flag = false;
						for (auto& person: clientsOfLibrary){
							if (person.getId() == myId){
								flag = true;
								person.addBook(temp);
								break;
							}
						}
						if (!flag){
							string firstName, lastName;
							int age;
							cout << "You need to create account" << endl;
							cout << "Input your first name" << endl;
							cin >> firstName;
							cout << "Input your last name" << endl;
							cin >> lastName;
							cout << "Input your age" << endl;
							cin >> age;
							clientsOfLibrary.push_back(Person(personID, firstName, lastName, age));
							clientsOfLibrary.back().addBook(temp);
							personID++;
						}
						cout << "You successfully took a book" << endl;
					}
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
					for (auto& book: booksOfLibrary){
						vector<string> now = book.getGenres();
						if (find(now.begin(), now.end(), genre_) != now.end()){
							book.showBook();
						}
					}
				}
				else if (choose == 2){
					string author_;
					cout << "Input prefered author" << endl;
					cin >> author_;
					for (char& c: author_){
						c = tolower(c);
					}
					author_[0] = toupper(author_[0]);
					for (auto& book: booksOfLibrary){
						vector<string> now = book.getGenres();
						if (find(now.begin(), now.end(), author_) != now.end()){
							book.showBook();
						}
					}
				}
				else if (choose == 3){
					int left = 0, right = 0;
					cout << "Input from what year to search" << endl;
					cin >> left;
					cout << "Input to what year to search" << endl;
					cin >> right;
					for (auto& book: booksOfLibrary){
						vector<string> now = book.getGenres();
						int yearOfBook = book.getYear();
						if (yearOfBook >= left && yearOfBook <= right){
							book.showBook();
						}
					}
				}
				else{
					cout << "Don't know the command, please try again" << endl;
				}
				break;
			}
			case 3:
			{
				for (auto& person: clientsOfLibrary){
					person.showPerson();
				}
				break;
			}
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
