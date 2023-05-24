#include "pch.h"
#include "loyality.h"
#include <iostream>

using namespace std;

LoyaltySystem::LoyaltySystem(){
}

LoyaltySystem::LoyaltySystem( std::string phoneNumber) {
    this->phoneNumber = phoneNumber;
    loyaltyPoints = 0;
}

string LoyaltySystem::getPhoneNumber() const {
    return phoneNumber;
}

int LoyaltySystem::getLoyaltyPoints() const {
    return loyaltyPoints;
}

void LoyaltySystem::addPointsByPurchase(int totalPrice) {
    int pointsToAdd = totalPrice / 10; // Assuming 1 loyalty point for every 10 units of purchase
    loyaltyPoints += pointsToAdd;
    cout << pointsToAdd << " loyalty points added to LoyaltySystem with phone number " << phoneNumber << "." << endl;
}


double LoyaltySystem::convertPointsToMoney(int points) {
	double money = points * 0.01; // Assuming 1 loyalty point equals $0.01
	cout << points << " loyalty points converted to $" << money << " for LoyaltySystem with phone number " << phoneNumber << "." << endl;
	return money;
}

// Method to convert loyalty points to actual money
double LoyaltySystem::pointsInMoney(){
    double money = loyaltyPoints * 0.01; // Assuming 1 loyalty point equals $0.01
    cout << loyaltyPoints << " loyalty points converted to $" << money << " for LoyaltySystem with phone number " << phoneNumber << "." << endl;
    loyaltyPoints = 0; // Reset loyalty points after conversion
    return money;
}

void LoyaltySystem::addLoyaltyPoints(int points) {
    loyaltyPoints += points;
}

void LoyaltySystem::deductLoyaltyPoints(int points) {
    if (loyaltyPoints >= points) {
        loyaltyPoints -= points;
    }
    else {
        cout << "Insufficient loyalty points in LoyaltySystem with phone number " << phoneNumber << "." << endl;
    }
}

void LoyaltySystem::setPhoneNumber(string phoneNumber) {
	this->phoneNumber = phoneNumber;
}

void LoyaltySystem::setLoyaltyPoints(int loyaltyPoints) {
	this->loyaltyPoints = loyaltyPoints;
}
