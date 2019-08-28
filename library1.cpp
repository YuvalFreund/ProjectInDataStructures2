#include "library1.h"
#include "Oasis.h"
using namespace oasis;

void* init(){
    Oasis * DS = new Oasis();
    return (void*)DS;
}
/* Description:   Adds a new player.
 * Input:         DS - A pointer to the data structure.
 *                playerID - The ID of the player to add.
 *				  initialCoins - The amount of coins the player has.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, playerID <= 0, initialCoins < 0.
 *                FAILURE - If playerID is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType addPlayer(void *DS, int playerID, int initialCoins){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->addPlayer(playerID, initialCoins);
}

/* Description:   Adds a new empty clan to the system.
 * Input:         DS - A pointer to the data structure.
 *                clanID - The new clan's ID.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or clanID <= 0.
 *                FAILURE - If clanID is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType addClan(void *DS, int clanID){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->addClan(clanID);
}

/* Description:   Moves player playerID to clan clanID.
 * Input:         DS - A pointer to the data structure.
 *                playerID - The ID of the player.
 *				  clanID - The ID of the clan to assign the player to
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, playerID <= 0 or clanID <= 0.
 *                FAILURE - If playerID or clanID aren't in the DS, or if playID is already in a clan.
 *                SUCCESS - Otherwise.
 */
StatusType joinClan(void *DS, int playerID, int clanID){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->joinClan(clanID,playerID);
}

/* Description:   Returns the player that has completed the most challanges in clanID
 * 			      If clanID < 0, returns the player that has completed the most challanges in the entire DS.
 * Input:         DS - A pointer to the data structure.
 *                clanID - The clan that we would like to get the data for.
 * Output:        playerID - A pointer to a variable that should be updated to the ID of the player with the most completed challanges.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if playerID == NULL, or if clanID == 0.
 *                FAILURE - If clanID > 0 and clanID doesn't exist in the DS
 *                SUCCESS - Otherwise.
 */
StatusType getBestPlayer(void *DS, int clanID, int *playerID){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->getBestPlayer(clanID,playerID);
}

/* Description:   Adds coins to playerID
 * Input:         DS - A pointer to the data structure.
 *                playerID - The player that has completed a challange
 *                coins - The amount of coins playerID received for completing the challange
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, or if playerID <= 0, or if coins <= 0.
 *                FAILURE - if playerID > 0 and playerID doesn't exist in the DS
 *                SUCCESS - Otherwise.
 */
StatusType completeChallange(void *DS, int playerID, int coins){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->completeChallenge(playerID,coins);
}

/* Description:   Returns all the players in clan clanID sorted by their amount of coins.
 *           	  If clanID < 0, returns all the players in the entire DS sorted by their coins.
 * Input:         DS - A pointer to the data structure.
 *                clanID - The clan that we would like to get the data for.
 * Output:        players - A pointer to a to an array that you should update with the players' IDs sorted by their coins,
 *			                  in case two players have same power, they should be sorted by their ID.
 *                numOfPlayers - A pointer to a variable that should be updated to the number of returned players.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If any of the arguments is NULL or if clanID == 0.
 *                FAILURE - if clanID > 0 and clanID doesn't exist in the DS
 *                SUCCESS - Otherwise.
 */
StatusType getScoreboard(void *DS, int clanID, int **players, int *numOfPlayers){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->getScoreBoard(clanID,players,numOfPlayers);
}

/* Description:   Joins two clans, leaving the players with no comlpeted challanges out of the new clan.
 * Input:         DS - A pointer to the data structure.
 *                clanID1 - ID of the first clan.
 *		          clanID2 - ID of the second clan.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if clanID1<=0, or if clanID2<=0
 *                FAILURE - If clanID1 or clanID2 are not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType uniteClans(void *DS, int clanID1, int clanID2){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->uniteClans(clanID1, clanID2);
}

/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void quit(void** DS){
    if(DS!=NULL && *DS!=NULL){
        delete (Oasis*)*DS;
        *DS = NULL;
    }
}

void printDS(void* DS){
    ((Oasis *)DS)->print();

}
