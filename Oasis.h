#ifndef WET1_OASIS_H
#define WET1_OASIS_H

#include "Player.h"
#include "Clan.h"
#include "AVLTree.h"
#include "library1.h"
#include <iostream>
namespace oasis {
    /**
    * Oasis definition
    */
    class Oasis {
        AVLTree<Player> coin_player;
        AVLTree<Player> id_player;
        AVLTree<Clan> clans;
        int num_players;
        int id_bestPlayer;
        int challenges_bestPlayer;
    public:
        /**
         * Constructor
         * sets all trees and values to 0. if failed returns NULL;
         */
        Oasis();


        /**
       * addPlayer
       * @param player's id
       * @param player's initial coins
         * the player is not associated with a tribe
       * @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
       */
        StatusType addPlayer(int player_id, int initial_coins);

        /**
       * addClan
       * @param clan's id
       * @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
       */
        StatusType addClan(int clan_id);

        /**
       * joinClan
       * @param clan's id
       * @param player's id
         * if the player is a part of the game, it's added to the clan specified (unless already in a clan)
       * @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
       */
        StatusType joinClan(int clan_id,int player_id);

        /**
       * completeChallenge
       * @param coins
       * @param player's id
         * the player with the specified ID finished a challenge and received X coins
       * @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
       */
        StatusType completeChallenge(int player_id, int coins);

        /**
        * getBestPlayer
        * @param clan's id
        * @param player pointer
        * the player with the maximum amount of challenges according to the rules
       * @returns SUCCESS,FAILURE,INVALID_INPUT
       */
        StatusType getBestPlayer(int clan_id,int *player_id);

        /**
        * getScoreBoard
        * @param players array
         * numPlayers
        * @param clan's id
        * returns all the players in clan sorted by their coins. if clanId<0 than
         * return all the players in the system sorted
       * @returns SUCCESS,FAILURE,INVALID_INPUT
       */
        StatusType getScoreBoard(int clan_id, int **players, int *numPlayers);

        /**
        * uniteClans
        * @param clan's id
        * sets a new tribe from the two given as specified by the rules
       * @returns SUCCESS,FAILURE,INVALID_INPUT
       */
        StatusType uniteClans(int clan_id1, int clan_id2);

        /**
        * Quit
        * Exit the system and frees all data
       */
        void Quit();
        ~Oasis();
        void print();
    };
}



#endif //WET1_OASIS_H
