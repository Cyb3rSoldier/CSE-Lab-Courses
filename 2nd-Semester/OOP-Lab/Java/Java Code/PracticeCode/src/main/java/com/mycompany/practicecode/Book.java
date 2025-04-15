
package com.mycompany.practicecode;


    // Book class
public class Book {
    // Fields
    public String title;
    private String author;
    public int numberOfPages;

    // Default constructor
    public Book() {
        this.title = "Unknown";
        this.author = "Anonymous";
        this.numberOfPages = 0;
    }

    // Parameterized constructor
    public Book(String title, String author, int numberOfPages) {
        this.title = title;
        this.author = author;
        this.numberOfPages = numberOfPages;
    }

    // Method to display book information
    public void displayInfo() {
        System.out.println("Title: " + this.title);
        System.out.println("Author: " + this.author);
        System.out.println("Number of Pages: " + this.numberOfPages);
    }

    // Main method to test the Book class
    public static void main(String[] args) {
        // Creating a Book object using the default constructor
        Book defaultBook = new Book();
        // Creating a Book object using the parameterized constructor
        Book customBook = new Book("1984", "George Orwell", 328);

        // Displaying information of both books
        System.out.println("Default Book Info:");
        defaultBook.displayInfo();
        System.out.println();
        

        System.out.println("Custom Book Info:");
        customBook.displayInfo();
    }
}


