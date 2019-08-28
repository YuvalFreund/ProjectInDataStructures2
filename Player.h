#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include <iostream>
namespace oasis{
    class Clan;

    /**
    * Player definition
    */
    class Player{
        int id;
        int coins;
        int challenges;
        Clan* clan;
    public:

        /**
         * Constructor
         * @param player's id
         * @param player's initial coins
         * challenges will be set to 0 when constructed, clan set to NULL
         * @throws PlayerInvalidArgs If at least one of the arguments is
         *  invalid, or both adults and children are 0.
         */
        Player(int id, int coins = 0);
        Player();
        /**
         * Copy constructor
         * @param other The group to copy
         */
        Player(const Player& other);

        /** Destructor
         */
        ~Player();

        /**
         * Get the id of the player
         * @return id
         */
        int getId() const;

        /**
         * Get the challenges of the player
         * @return challenges
         */
        int getChallenges() const;

        /**
         * Get the amount of coins the player has
         * @return  coins
         */
        int getCoins() const;

        /**
         * Get the clan's pinter
         * @return  clan's pinter
         */
        Clan* getClan() const;

        /**
         * Set the challenges of the player
         */
        void setChallenges(int challenges);

        /**
         * Set the coins of the player
         */
        void setCoins(int coins);

            /**
        * Set the clan of the player
        */
        void setClan(Clan* clan);

        /**
         * Compare two players. according to challenges and id
         * @param other
         * @return true, if there are less challenges or id is bigger
         *  false otherwise.
         */
        bool operator<(const Player& other) const;

        /**
         * Compare two players. according to challenges and id
         * @param other
         * @return true, if there are more challenges or id is less
         *  false otherwise.
         */
        bool operator>(const Player& other) const;

        /**
         * Compare two player according to coins and id
         * @param other
         * @return true, if there are more coins and id is less
         *  false otherwise.
         */
        bool operator<=(const Player& other) const;

    };
    std::ostream& operator<<(std::ostream& os, const Player& player);

} // namespace oasis

#endif //WET1_PLAYER_H
