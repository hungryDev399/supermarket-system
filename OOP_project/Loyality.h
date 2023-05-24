#pragma once
#include <string>

class LoyaltySystem {
public:
    LoyaltySystem( std::string phoneNumber);
    LoyaltySystem();
    std::string getPhoneNumber() const;
    int getLoyaltyPoints() const;
    void addPointsByPurchase(int totalPrice);
    double pointsInMoney();
    void addLoyaltyPoints(int points);
    void deductLoyaltyPoints(int points);
    void setPhoneNumber(std::string phoneNumber);
    void setLoyaltyPoints(int loyaltyPoints);
    double convertPointsToMoney(int points);
private:
    std::string phoneNumber;
    int loyaltyPoints;
};

