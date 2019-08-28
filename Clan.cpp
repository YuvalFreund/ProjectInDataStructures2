#include <iostream>
#include "Clan.h"
using namespace oasis;
using namespace std;
    class checkChallenges{
    public:
        bool operator()(Player* p){
            return p->getChallenges()>0;
        }
    };
class setToNULL{
public:
    void operator()(Player* p){
         p->setClan(NULL);
    }
};
class setToClan{
     Clan* toAdd;
public:
    setToClan(Clan* clan) : toAdd(clan){}
    void operator()(Player* p){
        p->setClan(toAdd);
    }
};
    class compare_PlayerCoins{
    public:
        int operator()(Player* p1, Player* p2){
             if(p1->getCoins() == p2->getCoins()) {
                 if (p1->getId() > p2->getId()) {
                     return 2;
                 } else if(p1->getId() < p2->getId()) {
                     return 1;
                 } else
                 return 0;
             }
            return p1->getCoins() > p2->getCoins() ? 1:2;
        }
    };
    Clan::Clan(int CLANID) : CLANID(CLANID), numPlayers(0), bestPlayerId(-1),
                             bestPlayerScore(-1),
                       players(AVLTree<Player*>()) {
        if(CLANID<=0){
            throw ClanInvalidArgs();
        }
    }
    /**
     * Copy constructor
     * @param other Clan to copy
     */
    Clan::Clan(const Clan& other){
        this->CLANID = other.CLANID;
        this->numPlayers = other.numPlayers;
        this->bestPlayerScore = other.bestPlayerScore;
        this->bestPlayerId = other.bestPlayerId;
        this->players.setRoot(other.players.getRoot());
    }
Clan& Clan::operator=(const Clan& other){
    this->CLANID = other.CLANID;
    this->numPlayers = other.numPlayers;
    this->bestPlayerScore = other.bestPlayerScore;
    this->bestPlayerId = other.bestPlayerId;
    this->players.setRoot(other.players.getRoot());
    return *this;
}
    /**
     *
     * Destructor
     */
    Clan::~Clan(){
      //  players.destroyTree(players.getRoot());
    }

    Clan::Clan(){}
    /**
     * Get the id of the Clan
     * @return id
     */
    int Clan::getId() const{
        return this->CLANID;
    }
        /**
        * set the id of the Clan
        * @return id
        */
        void Clan::setId(int ID)  {
            CLANID=ID;
        }
        /**
        * set the id of the Clan
        * @return id
        */
        void Clan::setNumPlayers(int newNumPlayers)  {
            numPlayers=newNumPlayers;
        }

    /**
     * Gets the ID of the best player (player with most challenges)
     */
    int Clan::getBestPlayerID() const{
        return this->bestPlayerId;
    }
    /**
     * Gets the Score of the best player (player with most challenges)
      */
    int Clan::getBestPlayerScore() const{
        return this->bestPlayerScore;
    }
    /**
     * Get the number of players
     */
    int Clan::getNumPlayers() const{
        return this->numPlayers;
    }
    /**
     * Compare two Clans according to CLANID
     * @param other
     * @return true, if ID of other is bigger than this.
     *  false otherwise.
     */
    bool Clan::operator<(const Clan& other) const{
        return  this->getId() < other.getId();
    }

    /**
     * Compare two Clans according to CLANID
     * @param other
     * @return true, if ID of this is bigger than other.
     *  false otherwise.
     */
    bool Clan::operator>(const Clan& other) const{
        return this->getId() > other.getId();
    }

    void Clan::setPlayersToNull(){
        this->players.setRoot(NULL);
    }
    void Clan::destroyPlayers(){
        this->players.destroyTree(this->players.getRoot());
    }
    /**
     * Merge two Clans according
     * @param other clan to merge with
     * merge both player trees
     * return the id of the clan to be removed
     */
    int Clan::unite(Clan& other) {
        int idForReturn = getId();
        if(numPlayers < other.numPlayers ||
           (numPlayers == other.numPlayers && CLANID > other.getId())) {
            other.setNumPlayers(other.players.mergeTrees
                    (players, compare_PlayerCoins(),
                    checkChallenges(),setToNULL(),setToClan(this)));
                    this->destroyPlayers();
                    this->setPlayersToNull();
            if (bestPlayerScore > other.bestPlayerScore ||
                (bestPlayerScore == other.bestPlayerScore &&
                 bestPlayerId < other.bestPlayerId)) {
                other.bestPlayerScore = bestPlayerScore;
                other.bestPlayerId = bestPlayerId;
            }
            if(other.getNumPlayers() == 0){
                other.bestPlayerScore = -1;
                other.bestPlayerId = -1;
            }
        }else{
            numPlayers = players.mergeTrees(other.players, compare_PlayerCoins(),
                                            checkChallenges(),setToNULL(),
            setToClan(&other));
            idForReturn = other.getId();
            other.destroyPlayers();
            other.setPlayersToNull();
            if (bestPlayerScore < other.bestPlayerScore ||
                (bestPlayerScore == other.bestPlayerScore &&
                 bestPlayerId > other.bestPlayerId)) {
                bestPlayerScore = other.bestPlayerScore;
                bestPlayerId = other.bestPlayerId;
            }
            if(getNumPlayers() == 0){
                bestPlayerScore = -1;
                bestPlayerId = -1;
            }
        }
        return idForReturn;
    }
    /**
     * insert a player in to the tree
     * @param player to be entered
     * checks if player is better than current best player
     * function in oasis gets id and returns player!!
     */
    void Clan::insertPlayer(Player* player) {
        if(player->getChallenges() > bestPlayerScore||
                (player->getChallenges() == bestPlayerScore &&
                player->getId()<getBestPlayerID())){
            bestPlayerScore = player->getChallenges();
            bestPlayerId = player->getId();
        }
        player->setClan(this);
        numPlayers++;
        this->players.insert(player,compare_PlayerCoins());
    }
    /**
    * remove a player from the tree
    * @param player to be removed
    */
    void Clan::removePlayer(Player* player) {
        players.remove(player,compare_PlayerCoins());
        numPlayers--;
    }
    /**
     * remove a player from the tree
     * @param player to be removed
     */
    Player** Clan::findPlayer(Player* player) {
        return  players.find(player,compare_PlayerCoins());
    }

    /**
      * output the id of all players sorted by coins a player in to the tree
      * @param players- array to enter all the id
      * @param playersNum- to enter number of players
      * checks if player is better than current best player
      */
    void Clan::scoreBoard(int** playersArr, int* playersNum){
        *playersNum = numPlayers;
        Player** tempRes = new Player*[numPlayers];
        players.Cleaninorder(tempRes);
        int *tempArr;
        tempArr = (int*)malloc(sizeof(int)*numPlayers);
        for(int i=0; i<numPlayers; i++){
            tempArr[i] = tempRes[numPlayers-i-1]->getId();
        }
        *playersArr=tempArr;
        delete[](tempRes);
    }
    void Clan::displayPlayers(){
        players.display();
    }
    void Clan::updateChallenge(Player* ptr ,int coinsToAdd, int challangesToAdd){
        players.remove(ptr,compare_PlayerCoins());
        ptr->setCoins(coinsToAdd);
        ptr->setChallenges(challangesToAdd);
        players.insert(ptr,compare_PlayerCoins());
        if(ptr->getChallenges() > bestPlayerScore||
           (ptr->getChallenges() == bestPlayerScore &&
            ptr->getId()<getBestPlayerID())){
            bestPlayerScore = ptr->getChallenges();
            bestPlayerId = ptr->getId();
        }
    }

std::ostream& oasis::operator<<(std::ostream &os, const Clan &clan){
    os << clan.getId()<< "," << clan.getNumPlayers();
    return os;
}
