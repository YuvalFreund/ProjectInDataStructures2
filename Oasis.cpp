#include <iostream>
#include "Player.h"
#include "Oasis.h"
#include "Clan.h"

using namespace oasis;

class compare_coins{
public:
    int operator()(const Player& p1,const Player& p2)const{
        if(p1.getCoins() == p2.getCoins()) {
            if (p1.getId() > p2.getId()) {
                return 2;
            } else if(p1.getId() < p2.getId()) {
                return 1;
            } else
                return 0;
        }
        return p1.getCoins() > p2.getCoins() ? 1:2;
    }
};
class compare_challenge{
public:
    int operator()(const Player& num1,const Player& num2)const{
        if(num1.getId() == num2.getId())return 0;
        else if(num1.getChallenges() > num2.getChallenges() ||
                num1.getId() < num2.getId())return 2;
        else return 1;
    }
};
class compare_id_player{
public:
    int operator()(const Player& num1,const Player& num2)const{
        if(num1.getId() == num2.getId())return 0;
        else if(num1.getId() > num2.getId())return 1;
        else return 2;
    }
};
class compare_id_clan{
public:
    int operator()(const Clan& num1,const Clan& num2)const{
        if(num1.getId() == num2.getId())return 0;
        else if(num1.getId() > num2.getId())return 1;
        else return 2;
    }
};

/**
     * Constructor
     * sets all trees and values to 0. if failed returns NULL;
     */
Oasis::Oasis(): coin_player(), id_player(), clans(), num_players(0),
                id_bestPlayer(-1), challenges_bestPlayer(-1) {}


/**
* addPlayer
* @param player's id
* @param player's initial coins
 * the player is not associated with a tribe
* @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
*/
StatusType Oasis::addPlayer(int player_id, int initial_coins){
    try {
        if (this == NULL || player_id <= 0 || initial_coins < 0) {
            return INVALID_INPUT;
        }
        Player inserted1(player_id, initial_coins);
        Player inserted2(player_id, initial_coins);
        ///add player to tree sorted by coins and by id
        id_player.insert(inserted2, compare_id_player());
        coin_player.insert(inserted1, compare_coins());
        num_players++;///increase players in system
        if (challenges_bestPlayer < inserted1.getChallenges()) {
            ///change the best player if id is smallest
            id_bestPlayer = player_id;
            challenges_bestPlayer = inserted1.getChallenges();
        }
        else if(challenges_bestPlayer == inserted1.getChallenges()){
            if (id_bestPlayer > player_id) {
                id_bestPlayer = player_id;///challenges neccesarily 0
                challenges_bestPlayer = inserted1.getChallenges();
            }
        }
    }catch(const std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* addClan
* @param clan's id
* @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
*/
StatusType Oasis::addClan(int clan_id){
    try {
        if (this == NULL || clan_id <= 0) {
            return INVALID_INPUT;
        }
        Clan inserted(clan_id);
        ///add player to tree sorted by coins and by id
        clans.insert(inserted, compare_id_clan());
    }catch(const std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}
    /**
    * joinClan
    * @param clan's id
    * @param player's id
    * if the player is a part of the game, it's added to the clan specified (unless already in a clan)
    * @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
    */
StatusType Oasis::joinClan(int clan_id,int player_id){
    try {
        if (this == NULL || player_id <= 0 || clan_id <= 0) {
            return INVALID_INPUT;
        }
        Player *player = ((id_player.find(player_id,compare_id_player())));
        Clan *clan = (clans.find(Clan(clan_id),compare_id_clan()));
        ///check if player and clan are found and player doesnt have a tribe already
        if(player == NULL || clan == NULL || player->getClan()!=NULL)
            return FAILURE;
        clan->insertPlayer(player);
    }catch(const std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* completeChallenge
* @param coins
* @param player's id
 * the player with the specified ID finished a challenge and received X coins
* @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
*/
StatusType Oasis::completeChallenge(int player_id, int coins){
    try {
        if (this == NULL || player_id <= 0 || coins <= 0) {
            return INVALID_INPUT;
        }
        if(id_player.find(player_id,compare_id_player()) == NULL)
            return FAILURE;
        Player pID(*id_player.find(player_id,compare_id_player()));
        Player pCoins(*coin_player.find(pID,compare_coins()));
        coin_player.remove(pCoins,compare_coins());//remove from tree
        pCoins.setChallenges(pCoins.getChallenges()+1);
        pCoins.setCoins(pCoins.getCoins()+coins);//update coins
        coin_player.insert(pCoins,compare_coins());//insert to right place
        ///look for player in player's clan tree and update it
        if(pID.getClan()==NULL){
            Player *PID2=(id_player.find(player_id,compare_id_player()));
            PID2->setChallenges(PID2->getChallenges()+1);
            PID2->setCoins(PID2->getCoins()+coins);
        } else {
            int coinsToAdd = coins + pID.getCoins();
            int challangesToAdd = pID.getChallenges() + 1;
            Player *ptr = id_player.find(pID, compare_id_player());
            Clan *toInsert = ptr->getClan();
            toInsert->updateChallenge(ptr, coinsToAdd, challangesToAdd);
        }
            ///check if this player is the best fo them all
            if (pCoins.getChallenges() > challenges_bestPlayer ||
                (pCoins.getChallenges() == challenges_bestPlayer &&
                 pCoins.getId() < id_bestPlayer)) {
                challenges_bestPlayer = pCoins.getChallenges();
                id_bestPlayer = pCoins.getId();
            }
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* getBestPlayer
* @param clan's id
* @param player pointer
* the player with the maximum amount of challenges according to the rules
* @returns SUCCESS,FAILURE,INVALID_INPUT
*/
StatusType Oasis::getBestPlayer(int clan_id,int *player_id){
    try {
        if (this == NULL || clan_id == 0 || player_id == NULL) {
            return INVALID_INPUT;
        }
        ///look for clan
        if(clan_id>0){
            Clan *clan = clans.find(clan_id,compare_id_clan());
            if(clan == NULL)return FAILURE;
            *player_id = clan->getBestPlayerID();
        }
        else{
            *player_id = id_bestPlayer;
        }
    }catch(std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* getScoreBoard
* @param players array
 * numPlayers
* @param clan's id
* returns all the players in clan sorted by their coins. if clanId<0 than
 * return all the players in the system sorted
* @returns SUCCESS,FAILURE,INVALID_INPUT
*/
StatusType Oasis::getScoreBoard(int clan_id, int **players, int *numPlayers){
    try {
        if (this == NULL || clan_id == 0 || players == NULL || numPlayers == NULL){
            return INVALID_INPUT;
        }
        ///look for clan
        if(clan_id>0){
            Clan *clan = clans.find(clan_id,compare_id_clan());
            if(clan == NULL){
                return FAILURE;
            }///there's no clan with this ID
            else if(clan->getNumPlayers() == 0) {
                *players = NULL;
                *numPlayers = 0;
                return SUCCESS;
            }
            clan->scoreBoard(players,numPlayers);
        }
        else{
            if(num_players == 0){
                *players = NULL;
                *numPlayers = 0;
                return SUCCESS;
            }
            Player* temp = new Player[num_players];
            coin_player.Cleaninorder(temp);
            int *tempArr = (int*) malloc(sizeof(int)*num_players);
            for(int i=0;i<num_players;i++){
                tempArr[num_players-i-1] = temp[i].getId();
            }
            *players = tempArr;
            *numPlayers = this->num_players;
            delete[] temp;
        }
    }catch(std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* uniteClans
* @param clan's id
* sets a new tribe from the two given as specified by the rules
* @returns SUCCESS,FAILURE,INVALID_INPUT
*/
StatusType Oasis::uniteClans(int clan_id1, int clan_id2){
    try {
        if (this == NULL || clan_id1 <= 0 || clan_id2 <= 0 ||
                clan_id1 == clan_id2){
            return INVALID_INPUT;
        }
        ///look for clan
        Clan *first = clans.find(clan_id1,compare_id_clan());
        Clan *other = clans.find(clan_id2,compare_id_clan());
        if(first == NULL || other == NULL)return FAILURE;///there's no clan with this ID
        if(first->getNumPlayers() == 0 && other->getNumPlayers() == 0){
            if(first->getId() > other->getId())
                clans.remove(*first,compare_id_clan());
            else
                clans.remove(*other,compare_id_clan());
            return SUCCESS;
        }
        else if(first->getNumPlayers() == 0){
            clans.remove(*first,compare_id_clan());
            return SUCCESS;
        }
        else if(other->getNumPlayers() == 0){
            clans.remove(*other,compare_id_clan());
            return SUCCESS;
        }
        else {
            int IdToRemove = first->unite(*other);
            clans.remove(IdToRemove, compare_id_clan());
        }
    }catch(std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* Quit
* Exit the system and frees all data
*/
void Oasis::Quit(){

}
Oasis::~Oasis(){}
void Oasis::print(){
    printf("Coin Player Tree");
    coin_player.display();printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("ID Player Tree");
    id_player.display();printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Clans Tree");
    clans.display();printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    std::cout<<"num Players: " << num_players << " best_player: "
             << id_bestPlayer << " C.B: " << challenges_bestPlayer<<std::endl;
}