#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Smolproject 3 - Space and time

// Define a Card struct
struct Card {
    int suit;  // 0: Hearts, 1: Diamonds, 2: Clubs, 3: Spades
    int rank;  // 2-14 (adjusted for ace handling)
};

// Function to convert a single integer (0-51) to a Card object
Card intToCard(int cardValue) {
    Card card;
    card.suit = cardValue / 13;
    card.rank = cardValue % 13 + 2;  // Adjust for ace (14 or 1)
    if (card.rank == 14) {
        card.rank = 1;  // Handle ace as 1 for straight calculations
    }
    return card;
}

// Function to convert a Card object back to a single integer (0-51)
int cardToInt(const Card& card) {
    return card.suit * 13 + card.rank - 2;
}

// Function to check if a hand has a straight (including wrapping around ace)
bool hasStraight(const vector<Card>& hand) {
    vector<int> ranks;
    for (const Card& card : hand) {
        ranks.push_back(card.rank);
    }

    sort(ranks.begin(), ranks.end());

    // Check for regular straight (4 consecutive ranks)
    for (int i = 0; i < ranks.size() - 4; i++) {
        if (ranks[i + 4] - ranks[i] == 4) {
            return true;
        }
    }

    // Check for wrapping straight (ace as 1 or 14)
    if (ranks[0] == 1 && ranks[4] == 5) {
        return true;
    }

    return false;
}

// Function to check if a hand has a flush (all cards of the same suit)
bool hasFlush(const vector<Card>& hand) {
    int suit = hand[0].suit;
    for (const Card& card : hand) {
        if (card.suit != suit) {
            return false;
        }
    }
    return true;
}

// Function to check if a hand has a straight flush (straight and flush combined)
bool hasStraightFlush(const vector<Card>& hand) {
    return hasStraight(hand) && hasFlush(hand);
}

int main() {
    // Example hand (change these values to test different hands)
    // Could easily randomize hand if wanted
    vector<int> cardValues = {27, 39, 40, 41, 42}; // Example: 7, 10, J, Q, K (straight flush)

    // Convert card values to Card objects
    vector<Card> hand;
    for (int value : cardValues) {
        hand.push_back(intToCard(value));
    }

    // Check for straight, flush, and straight flush
    if (hasStraightFlush(hand)) {
        cout << "The hand has a straight flush!" << endl;
    } else if (hasStraight(hand)) {
        cout << "The hand has a straight." << endl;
    } else if (hasFlush(hand)) {
        cout << "The hand has a flush." << endl;
    } else {
        cout << "The hand does not have a straight, flush, or straight flush." << endl;
    }

    return 0;
}