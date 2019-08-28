#include <iostream>
#include "Player.h"
#include <ostream>

using namespace oasis;
///exceptions
    class PlayerInvalidArgs : public std::exception{};
    /**
     * Constructor
     * @param player's id
     * @param player's initial coins
     * challenges will be set to 0 when constructed, clan set to NULL
     * @throws PlayerInvalidArgs If at least one of the arguments is
     *  invalid, or both adults and children are 0.
     */
    Player::Player(int id, int coins) : id(id),coins(coins){
        if(id<0 || coins<0) {
            throw PlayerInvalidArgs();
        }
        this->challenges = 0;
        this->clan = NULL;
    }
    Player::Player(): id(0),coins(0), challenges(0), clan(NULL){}

    /**
     * Copy constructor
     * @param other The group to copy
     */
    Player::Player(const Player& other){
        this->id = other.id;
        this->clan = other.clan;
        this->challenges = other.challenges;
        this->coins = other.coins;
    }

    /** Destructor
     */
    Player::~Player(){}

    /**
     * Get the id of the player
     * @return id
     */
    int Player::getId() const {
        return this->id;
    }

    /**
    * Get the challenges of the player
    * @return challenges
    */
    int Player::getChallenges() const{
        return this->challenges;
    }

    /**
     * Get the amount of coins the player has
     * @return  coins
     */
    int Player::getCoins() const {
        return this->coins;
    }

    /**
     * Get the clan's pinter
     * @return  clan's pinter
     */
    Clan* Player::getClan() const {
        return this->clan;
    }

    /**
         * Set the challenges of the player
         */
    void Player::setChallenges(int challenges){
        this->challenges = challenges;
    }

    /**
     * Set the coins of the player
     */
    void Player::setCoins(int coins){
        this->coins = coins;
    }


    /**
     * Set the clan of the player
     */
    void Player::setClan(Clan* clan){
        this->clan = clan;
    }

    /**
     * Compare two players. according to challenges and id
     * @param other
     * @return true, if there are less challenges or id is bigger
     *  false otherwise.
     */
    bool Player::operator<(const Player& other) const {
        return (this->challenges < other.challenges ||
                this->id > other.id);
    }

    /**
     * Compare two players. according to challenges and id
     * @param other
     * @return true, if there are more challenges or id is less
     *  false otherwise.
     */
    bool Player::operator>(const Player& other) const {
        return (this->challenges > other.challenges ||
                this->id < other.id);
    }

    /**
     * Compare two player according to coins and id
     * @param other
     * @return true, if there are more coins or id is less
     *  false otherwise.
     */
    bool Player::operator<=(const Player& other) const {
        return (this->coins > other.coins ||
                this->id < other.id);
    }


    std::ostream& oasis::operator<<(std::ostream &os, const Player &player) {
       //os << player.getId() << "," << player.getCoins() << "," << player.getChallenges();
       os << player.getId()<<",";
        os << player.getCoins() << ","<< player.getClan();
        return os;
    }



