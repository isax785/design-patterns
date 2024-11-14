#include <iostream>
#include <vector>
#include <memory>
#include <string>

// std::shared_ptr for Book objects to demonstrate safe memory management and flexible ownership

class Book {
public:
    Book(const std::string& title, const std::string& author)
        : title_(title), author_(author) {}

    std::string GetTitle() const { return title_; }
    std::string GetAuthor() const { return author_; }

    friend std::ostream& operator << (std::ostream& os, const Book& book) {
        os << book.title_ << " by " << book.author_;
        return os;
    }

private:
    std::string title_;
    std::string author_;
};

class BookIterator {
public:
    BookIterator(const std::vector<std::shared_ptr<Book>>& books)
        : books_(books), index_(0) {}

    bool HasNext() const {
        return index_ < books_.size();
    }

    std::shared_ptr<Book> Next() {
        if (HasNext()) {
            return books_[index_++];
        } else {
            return nullptr;
        }
    }

private:
    const std::vector<std::shared_ptr<Book>>& books_;
    size_t index_;
};

class BookCollection {
public:
    void AddBook(const std::shared_ptr<Book>& book) {
        books_.push_back(book);
    }

    BookIterator CreateIterator() const {
        return BookIterator(books_);
    }

private:
    std::vector<std::shared_ptr<Book>> books_;
};

// Example usage
int main() {
    auto book1 = std::make_shared<Book>("1984", "George Orwell");
    auto book2 = std::make_shared<Book>("To Kill a Mockingbird", "Harper Lee");
    auto book3 = std::make_shared<Book>("The Great Gatsby", "F. Scott Fitzgerald");

    BookCollection collection;
    collection.AddBook(book1);
    collection.AddBook(book2);
    collection.AddBook(book3);

    BookIterator iterator = collection.CreateIterator();
    while (iterator.HasNext()) {
        std::shared_ptr<Book> book = iterator.Next();
        if (book) {
            std::cout << *book << std::endl;
        }
    }

    return 0;
}
