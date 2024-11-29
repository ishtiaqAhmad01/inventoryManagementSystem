#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int max_products = 300;

class Product {

private:
    int id;
    string name;
    string category;
    int price;
    int quantity;

public:
    Product(int id=0, string name="", string category="", int price=0, int quantity=0) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->quantity;
    }

    // 	---------------Getters------------------

    int get_id() {
        return this->id;
    }

    string get_name() {
        return this->name;
    }

    string get_category() {
        return this->category;
    }

    int get_price() {
        return this->price;
    }

    int get_quantity() {
        return this->quantity;
    }

    // 	---------------Setters------------------

    void set_id(int id) {
        this->id = id;
    }

    void set_name(string name) {
        this->name = name;
    }

    void set_category(string category) {
        this->category = category;
    }

    void set_price(int price) {
        this->price = price;
    }

    void set_quantity(int quantity) {
        this->quantity = quantity;
    }
};

class Inventory {
private:
    Product products[max_products];
    int product_counter;

public:
    Inventory() {
        product_counter = 0;
    }

    void add_product(Product product) {
        for (int i = 0; i < product_counter; i++) {
            if (products[i].get_id() == product.get_id()) {
                cout << "ID already exists." << endl;
                return;
            }
        }

        products[product_counter] = product;
        product_counter++;
        cout << "Product added successfully ✅" << endl;
        cout << "-----------------------------------------------------------" << endl;
    }

    void remove_product(int id)
    {
        for (int i = 0; i < product_counter; i++)
        {
            if (products[i].get_id() == id)
            {
                for (int j = i; j < product_counter - 1; j++)
                {
                    products[j] = products[j + 1];
                }
                product_counter--;
                cout<<"Product is removed Successfully ✅"<<endl;
                cout << "-----------------------------------------------------------" << endl;
                return;
            }
        }
        cout<<"Product not found 🚫"<<endl;
    }

    Product get_product(int id)
    {
        for (int i = 0; i < product_counter; i++)
        {
            if (products[i].get_id() == id)
            {
                return products[i];
            }
        }
        cout<<"Product not found"<<endl;
        return Product(-1, "", "", 0, 0);
    }

    void printProducts() {
        for (int i = 0; i < product_counter; i++) {
            cout << "ID : " << products[i].get_id() << endl;
            cout << "Name : " << products[i].get_name()<< endl;
            cout << "Category : " << products[i].get_category() << endl;
            cout << "Price : $" << products[i].get_price() << endl;
            cout << "Quantity : " << products[i].get_quantity() << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    void updateProduct(int id, string name, string category, int price, int quantity) {
        for (int i = 0; i < product_counter; i++) {
            if (products[i].get_id() == id) {
                products[i].set_name(name);
                products[i].set_category(category);
                products[i].set_price(price);
                products[i].set_quantity(quantity);
                cout << "Product updated successfully." << endl;
                cout << "-----------------------------------------------------------" << endl;
                return;
            }
        }
        cout << "ID does not exist." << endl;
    }

    void saveInventoryToFile(string filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file for writing." << endl;
            return;
        }

        for (int i = 0; i < product_counter; i++) {
            file << products[i].get_id() << ","
                 << products[i].get_name() << ","
                 << products[i].get_category() << ","
                 << products[i].get_price() << ","
                 << products[i].get_quantity() << endl;
        }

        file.close();
        cout << "Inventory saved to file." << endl;
    }

    void loadInventoryFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Could not open file for reading." << endl;
            return;
        }

        product_counter = 0;
        string line;
        while (getline(file, line) && product_counter < max_products) {
            int id, quantity;
            string name, category;
            double price;
            size_t pos = 0;

            pos = line.find(",");
            id = stoi(line.substr(0, pos));
            line = line.substr(pos + 1);

            pos = line.find(",");
            name = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find(",");
            category = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find(",");
            price = stod(line.substr(0, pos));
            line = line.substr(pos + 1);

            quantity = stoi(line);

            products[product_counter++] = Product(id, name, category, price, quantity);
        }

        file.close();
        cout << "Inventory loaded from file." << endl;
    }
};

int main() {
    Inventory inventory;
    cout << "-----------------------------------------------------------" << endl;
    cout << "---------------Inventory Management System ----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------------------------- Welcome! ------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    char choice;

    do {
        cout << "Please choose an option:" << endl;
        cout << "1. Add a product" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Find a product" << endl;
        cout << "4. Update a product" << endl;
        cout << "5. View all products" << endl;
        cout << "6. Save inventory to file" << endl;
        cout << "7. Load inventory from file" << endl;
        cout << "Q. Quit" << endl;
        cin >> choice;

        switch (choice) {
        case '1': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter product price: $ ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            Product product(id, name, category, price, quantity);
            inventory.add_product(product);
            break;
        }

        case '2': {
            int id;
            cout << "Enter product ID: ";
            cin >> id;
            inventory.remove_product(id);
            break;
        }

        case '3': {
            int id;
            cout << "Enter product ID: ";
            cin >> id;
            Product product = inventory.get_product(id);
            if (product.get_id()!=-1) {     // if id is -1 it means it is dummy product and product not found in indentory
                cout << "Name: " << product.get_name() << endl;
                cout << "Category: " << product.get_category() << endl;
                cout << "Price: $ " << product.get_price() << endl;
                cout << "Quantity: " << product.get_quantity() << endl;
                cout << "-----------------------------------------------------------" << endl;
            } else {
                cout << "Product not found." << endl;
            }
            break;
        }

        case '4': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter the product ID: ";
            cin >> id;
            cout << "Enter new product name: ";
            cin >> name;
            cout << "Enter new product category: ";
            cin >> category;
            cout << "Enter new product price: $ ";
            cin >> price;
            cout << "Enter new product quantity: ";
            cin >> quantity;
            inventory.updateProduct(id, name, category, price, quantity);
            break;
        }

        case '5': {
            inventory.printProducts();
            break;
        }

        case '6': {
            inventory.saveInventoryToFile("inventory.csv");
            break;
        }

        case '7': {
            inventory.loadInventoryFromFile("inventory.csv");
            break;
        }

        case 'q':
        case 'Q':
            cout << "Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (true);

    return 0;
}
