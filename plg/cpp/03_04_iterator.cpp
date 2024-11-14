#include <iostream>
#include <vector>
#include <string>

class Book {
public:
    Book(const std::string& title, const std::string& author)
        : title_(title), author_(author) {}

    std::string GetTitle() const { return title_; }
    std::string GetAuthor() const { return author_; }

    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << book.title_ << " by " << book.author_;
        return os;
    }

private:
    std::string title_;
    std::string author_;
};

class BookIterator {
public:
    BookIterator(const std::vector<Book>& books)
        : books_(books), index_(0) {}

    bool HasNext() const {
        return index_ < books_.size();
    }

    const Book& Next() {
        return books_[index_++];
    }

private:
    const std::vector<Book>& books_;
    size_t index_;
};

class BookCollection {
public:
    void AddBook(const Book& book) {
        books_.push_back(book);
    }

    BookIterator CreateIterator() const {
        return BookIterator(books_);
    }

private:
    std::vector<Book> books_;
};

// Example usage
int main() {
    Book book1("1984", "George Orwell");
    Book book2("To Kill a Mockingbird", "Harper Lee");
    Book book3("The Great Gatsby", "F. Scott Fitzgerald");

    BookCollection collection;
    collection.AddBook(book1);
    collection.AddBook(book2);
    collection.AddBook(book3);

    BookIterator iterator = collection.CreateIterator();
    while (iterator.HasNext()) {
        const Book& book = iterator.Next();
        std::cout << book << std::endl;
    }

    return 0;
}
