Objectives:
The objective of this project is to create a simple and efficient way to manage book inventories. The system uses file-based data storage to store details that can be easily accessed and updated. It is designed to implement features such as adding, viewing, deleting, and updating, making management easy and effective. 

https://github.com/user-attachments/assets/17568039-e4bc-4d23-9e0d-0eb1174f4f5e

Steps of the Entire Process:

• Created a text file to store the admin credentials and a csv file to store the book records.

• Declared a login() for both admin and guest users. For the admin log-in, the admin need to type their username and password for authentication, and for the guest log-in, guests can log in directly without credentials.

• Initially, the password entered by the administrator was visible, which raised privacy issues. To prevent others from seeing the password, I implemented a password asterisk(*) so that the password will not be visible.

• Then I declared adminmenu(), after logging in, the admin has the following operations: Add a book, display all books, search for a book, delete a book, update the book details. These operations are defined in a separate file BookStucture.cpp where the book structure and functions are implemented.

• For addbook(), the admin can enter details for a new book: ID, Title, Author name, Category, Price and Quantity. The details are then added to the csv file.

• For displaybook(), it will display all the books currently present in the inventory and show thedetails of ID, title, author, category, price, and quantity of all the books.

• For searchbook(), it allows the admins to search for a book in the inventory.Initially, the search required exact matching of characters, including captilization and whitespace. To improve usability, i implemented a normalizestring() and computesimilarity(). Converts the input and stored data to lowercase and removes extra spaces for consistent matching. It iterates through the characters of both strings, counts the number of matching characters, and computes the similarity. This ensures that books can be found even if the input has minor differences in case or formatting. The admins can search for the book by title, category, or price range.

• For deletebook(), it allows the admins to enter the title of the book to be deleted. It also uses normalizestring() and computesimilarity() so that the book can be easily found in the case of formatting. By typing the title, the book details will be shown. If they want to delete the book ,by typing Y the book will automatically be removed from the inventory.

• For updatebook(), it allows the admins to update the details of any book in the inventory. Admins can modify fields such as quantity, price, or any other detail. If the admin finishes their tasks or doesn’t want to perform additional operations, they can choose to exit.

• After declaring all the admin operations, I declared the guestmenu(), after logging in, the guest has the following operations for purchasing the books: Search for a book by BookId, search for a book by price.

• By selecting the search for a book by BookId, it will first display all books present in the inventory. The guest is prompted to enter the bookid of which books they want to purchase and also the quantity. Suppose that the number of copies is not the number of copies they want, then it will show the text ”Sorry only this much copies are available”. The books which are selected will be added to the cart if they want to purchase any other books, they can type the bookid and it will be added to the cart. A bill will be generated showing the details of their purchase.

• By selecting the search for a book by price, they can choose the price range: under 300, under 500, above 500

• By selecting the price range, it shows the books that fall under the selected price range. The guest can enter the bookid of the desired book and specify the quantity they wish to purchase. A bill is
automatically generated with the purchase details.

• After completing their purchases, guests can exit if they do not want to purchase additional books.
Similarly, the admin can exit after completing their operations.
