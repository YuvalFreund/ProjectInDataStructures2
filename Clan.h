
#ifndef WET1_CLAN_H
#define WET1_CLAN_H
#include "Player.h"
#include "AVLTree.h"
#include <iostream>
namespace oasis{
    /**
    * clan definition and functions
    */
    class Clan{
        int CLANID;
        int numPlayers;
        int bestPlayerId;
        int bestPlayerScore;
        AVLTree<Player*> players;
    public:
        class ClanInvalidArgs : public std::exception{};
        /**
         * Constructor
         * @param clan id
         * numplayers and best player id will be set to 0 when constructed
         * avlTree will be consturcted
         * @throws ClanInvalidArgs If CLANDID<=0
         */
         Clan();

         Clan(int CLANID);
        /**
         * Copy constructor
         * @param other The group to copy
         */
        Clan(const Clan& other);
        /**
         * assign operator
          * @param other The group to copy
          */
        Clan& operator=(const Clan& other);

            /** Destructor
             */
        ~Clan();

        /**
         * Get the id of the Clan
         * @return id
         */
        int getId() const;

        /**
         * set the id of the Clan
         */
        void setId(int ID);
        /**
        * set the id of the Clan
        */
        void setNumPlayers(int ID);


        /**
         * Gets the ID of the best player (player with most challenges)
         */
        int getBestPlayerID() const;


        /**
        * Gets the Score of the best player (player with most challenges)
        */
        int getBestPlayerScore() const;

        /**
         * Get the number of players
         */
        int getNumPlayers() const;

        /**
         * Compare two Clans according to CLANID
         * @param other
         * @return true, if ID of other is bigger than this.
         *  false otherwise.
         */
        bool operator<(const Clan& other) const;

        /**
         * Compare two Clans according to CLANID
         * @param other
         * @return true, if ID of this is bigger than other.
         *  false otherwise.
         */
        bool operator>(const Clan& other) const;

        /**
         * Merge two Clans according
         * @param other clan to merge with
         * merge both player trees, deleting the old Clan
         */
        int unite( Clan& other) ;

        /**
         * insert a player in to the tree
         * @param player to be entered
         * checks if player is better than current best player
         */
        void insertPlayer(Player* player);
        /**
          * remove a player from the tree
          * @param player to be removed
          */
        void removePlayer(Player* player);
        /**
        * finds a player from the tree
        * @param player to be removed
        */
        Player** findPlayer(Player* player);
        /**
       * output the id of all players sorted by coins a player in to the tree
       * @param player to be entered
       * checks if player is better than current best player
       */
        void scoreBoard(int** playersArr, int* playersNum);
        /**
        * output the id of all players
         */
        void displayPlayers();
        void updateChallenge(Player* ptr,int coinsToAdd, int challangesToAdd);

        ///updates the players tree to Null
        void setPlayersToNull();

        void destroyPlayers();

        };
    std::ostream& operator<<(std::ostream& os, const Clan& clan);

} // namespace oasis
#endif //WET1_CLAN_H
