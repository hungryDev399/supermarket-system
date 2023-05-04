#ifndef PRODUCT_H
#define PRODUCT_H


class PRODUCT {
private:
    std::string product_code;
    std::string name;
    std::string brand;
    std::string category;
    int stock_level;
    float price;
    bool is_pizza;

public:
    //setters
    void set_product_code(std::string product_code);
    void set_name(std::string name);
    void set_brand(std::string brand);
    void set_category(std::string category);
    void set_stock_level(int stock_level);
    void set_price(float price);
    void set_is_pizza(bool is_pizza);

    //getters
    std::string get_product_code() const;
    std::string get_name() const;
    std::string get_brand() const;
    std::string get_category() const;
    int get_stock_level() const;
    float get_price() const;
    bool get_is_pizza() const;

    //constructor
    PRODUCT();

    //methods
    void generatecode();
};

#endif 
