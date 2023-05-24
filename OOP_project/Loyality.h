#pragma once
#include <string>

class LoyaltySystem {
public:
    LoyaltySystem(const std::string& phoneNumber);
    LoyaltySystem();
    std::string getPhoneNumber() const;
    int getLoyaltyPoints() const;
    void addPointsByPurchase(int totalPrice);
    double convertPointsToMoney();
    void addLoyaltyPoints(int points);
    void deductLoyaltyPoints(int points);
    void setPhoneNumber(std::string phoneNumber);
    void setLoyaltyPoints(int loyaltyPoints);

private:
    std::string phoneNumber;
    int loyaltyPoints;
};

