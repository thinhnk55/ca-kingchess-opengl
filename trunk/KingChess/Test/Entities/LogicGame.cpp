#include "LogicGame.h"
#include "../Sences/GameSence.h"
#include <iostream>
using namespace std;

LogicGame::LogicGame()
{
    turn = Turn::RED;
}

LogicGame::~LogicGame()
{
}

bool LogicGame::isValidMoving(ExtraModel* firstCell, ExtraModel *secondCell){

    if(firstCell->associatedChessPieceIndex >= 8 && firstCell->associatedChessPieceIndex <= 15){//red pawn
        return checkPawnMoveRule(firstCell,secondCell,true);
    }
    
    if(firstCell->associatedChessPieceIndex >= 16 && firstCell->associatedChessPieceIndex <= 23){//blue pawn
        return checkPawnMoveRule(firstCell,secondCell,false);
    }

    if(firstCell->associatedChessPieceIndex == QUEEN_RED || firstCell->associatedChessPieceIndex == QUEEN_BLUE){
        return checkQueenMoveRule(firstCell, secondCell);
    }

    if(firstCell->associatedChessPieceIndex == BISHOP_BLUE_1 || firstCell->associatedChessPieceIndex == BISHOP_BLUE_2
        || firstCell->associatedChessPieceIndex == BISHOP_RED_1 || firstCell->associatedChessPieceIndex == BISHOP_RED_2
        )
    {
        return checkBishopMoveRule(firstCell,secondCell);
    }

    if(firstCell->associatedChessPieceIndex == ROOK_BLUE_1 || firstCell->associatedChessPieceIndex == ROOK_BLUE_2 
        || firstCell->associatedChessPieceIndex == ROOK_RED_2 || firstCell->associatedChessPieceIndex == ROOK_RED_1)
    {
        return checkRookMoveRule(firstCell,secondCell);
    }

    if(firstCell->associatedChessPieceIndex == KNIGHT_BLUE_1 || firstCell->associatedChessPieceIndex == KNIGHT_BLUE_2 
        || firstCell->associatedChessPieceIndex == KNIGHT_RED_1 || firstCell->associatedChessPieceIndex == KNIGHT_RED_2)
    {
        return checkKnightMoveRule(firstCell,secondCell);
    }

    if(firstCell->associatedChessPieceIndex == KING_RED || firstCell->associatedChessPieceIndex == KING_BLUE){
        return checkKingMoveRule(firstCell,secondCell);
    }

    return false;
}

void LogicGame::changeTurn(){
    if(turn == Turn::RED)
        turn = Turn::BLUE;
    else
        turn = Turn::RED;

    cout << "Turn: " << turn << endl;
}

bool LogicGame::checkPawnMoveRule(ExtraModel* firstCell, ExtraModel *secondCell,bool isRed){
    cout << "Firstcell: " << firstCell->boardIndexX << " " << firstCell->boardIndexY << endl;

    if(GameScene::inst().models[firstCell->associatedChessPieceIndex]->transformedToQueen == true){
        return checkQueenMoveRule(firstCell,secondCell);
    }

    else if(isRed){//tot do
        cout << "Kiem tra luat di tot do" << endl;
        if(secondCell->associatedChessPieceIndex == -1){//moving mode
            if((secondCell->boardIndexX == firstCell->boardIndexX)//di len 1 o
                &&(secondCell->boardIndexY == (firstCell->boardIndexY + 1))
                ){
                if(GameScene::inst().models[firstCell->associatedChessPieceIndex]->hasDoneFirstMove == false)
                    GameScene::inst().models[firstCell->associatedChessPieceIndex]->hasDoneFirstMove = true;
                cout << "di len mot o" << endl;
                return true;
            }
                
            if((secondCell->boardIndexX == firstCell->boardIndexX)//di len 2 o
                &&(secondCell->boardIndexY == (firstCell->boardIndexY + 2))
                && (GameScene::inst().models[firstCell->associatedChessPieceIndex]->hasDoneFirstMove == false)//xem da di nuoc dau tien chua
                )
            {
                ExtraModel* temp = getBoardCell(firstCell->boardIndexX, firstCell->boardIndexY + 1);
                //cout << temp->boardIndexX << " " << temp->boardIndexY << endl;
                if(temp->associatedChessPieceIndex == - 1){
                    cout << "di len hai o" << endl;
                    GameScene::inst().models[firstCell->associatedChessPieceIndex]->hasDoneFirstMove = true;
                    return true;
                }
            }

            return false; 
        }
        else{//fight mode
            cout << "kiem tra luat an tot do" << endl;
            if(firstCell->boardIndexX + 1 == secondCell->boardIndexX 
                && firstCell->boardIndexY + 1 == secondCell->boardIndexY
                )
                return true;

            if(firstCell->boardIndexX - 1 == secondCell->boardIndexX
                && firstCell->boardIndexY + 1 == secondCell->boardIndexY
                )
                return true;
        }
    }

    else if (!isRed){//tot den
        cout << "Kiem tra luat di tot den" << endl;
        if(secondCell->associatedChessPieceIndex == -1){//moving mode
            if((secondCell->boardIndexX == firstCell->boardIndexX)//di len 1 o
                &&(secondCell->boardIndexY == (firstCell->boardIndexY - 1))
                ){
                if(GameScene::inst().models[firstCell->associatedChessPieceIndex]->hasDoneFirstMove == false)
                    GameScene::inst().models[firstCell->associatedChessPieceIndex]->hasDoneFirstMove = true;
                cout << "di xuong mot o" << endl;
                return true;
            }
                
            if((secondCell->boardIndexX == firstCell->boardIndexX)//di len 2 o
                &&(secondCell->boardIndexY == (firstCell->boardIndexY - 2))
                && (GameScene::inst().models[firstCell->associatedChessPieceIndex]->hasDoneFirstMove == false)//xem da di nuoc dau tien chua
                )
            {
                ExtraModel* temp = getBoardCell(firstCell->boardIndexX, firstCell->boardIndexY - 1);
                //cout << temp->boardIndexX << " " << temp->boardIndexY << endl;
                if(temp->associatedChessPieceIndex == - 1){
                    cout << "di xuong hai o" << endl;
                    GameScene::inst().models[firstCell->associatedChessPieceIndex]->hasDoneFirstMove = true;
                    return true;
                }
            }

            return false; //di ko dung luat
        }
        else{//fight mode
            cout << "kiem tra luat an tot den" << endl;
            if(firstCell->boardIndexX - 1 == secondCell->boardIndexX 
                && firstCell->boardIndexY - 1 == secondCell->boardIndexY
                )
                return true;

            if(firstCell->boardIndexX + 1 == secondCell->boardIndexX
                && firstCell->boardIndexY - 1 == secondCell->boardIndexY
                )
                return true;
        }
    }
    return false;
}

bool LogicGame::checkQueenMoveRule(ExtraModel* firstCell, ExtraModel *secondCell){
    cout << " kiem tra luat di con hau" << endl;
    ExtraModel* temp = NULL;
    /*di thang*/
    if( (secondCell->boardIndexX == firstCell->boardIndexX)
        && (secondCell->boardIndexY != firstCell->boardIndexY)
        )
    {
        cout << "hau di thang" << endl;

        if(secondCell->boardIndexY > firstCell->boardIndexY){//di thang len tren
            if((secondCell->boardIndexY - firstCell->boardIndexY == 1))
                return true;
            
            for(int i = firstCell->boardIndexY + 1; i < secondCell->boardIndexY ; i++){
                temp = getBoardCell(firstCell->boardIndexX,i);
                if(temp->associatedChessPieceIndex != -1) {
                    return false; // co quan nam giua firstcell va secondcell
                }
            }
            return true;
        }

        if(secondCell->boardIndexY < firstCell->boardIndexY){//di thang xuong duoi

            if((secondCell->boardIndexY - firstCell->boardIndexY == -1))
                return true;

            for(int i = firstCell->boardIndexY - 1; i > secondCell->boardIndexY ; i--){
                temp = getBoardCell(firstCell->boardIndexX,i);
                if(temp->associatedChessPieceIndex != -1) 
                {
                    return false; // co quan nam giua firstcell va secondcell
                }
            }
            return true;
        }

    }

    /*di ngang*/
    else if( (secondCell->boardIndexY == firstCell->boardIndexY)
        && (secondCell->boardIndexX != firstCell->boardIndexX)
        )
    {
        cout << "hau di ngang" << endl;

        if(secondCell->boardIndexX < firstCell->boardIndexX){//di ngang sang trai
            if((secondCell->boardIndexX - firstCell->boardIndexX == -1))
                return true;

            for(int i = firstCell->boardIndexX - 1; i > secondCell->boardIndexX ; i--){
                temp = getBoardCell(i,firstCell->boardIndexY);
                if(temp->associatedChessPieceIndex != -1) return false; // co quan nam giua firstcell va secondcell
            }

            return true;
        }

        if(secondCell->boardIndexX > firstCell->boardIndexX){//di ngang sang phai
            if((secondCell->boardIndexX - firstCell->boardIndexX == 1))
                return true;

            for(int i = firstCell->boardIndexX + 1; i < secondCell->boardIndexX ; i++){
                temp = getBoardCell(i,firstCell->boardIndexY);
                if(temp->associatedChessPieceIndex != -1) return false; // co quan nam giua firstcell va secondcell
            }

            return true;
        }

    }

    /*di cheo*/
    else if( (secondCell->boardIndexY != firstCell->boardIndexY)
        && (secondCell->boardIndexX != firstCell->boardIndexX)
        )
    {
        cout << "kiem tra hau di cheo" << endl;
        if( (secondCell->boardIndexY > firstCell->boardIndexY)
        && (secondCell->boardIndexX > firstCell->boardIndexX)
        ) // di cheo ben phai len tren
        {
            if ((secondCell->boardIndexY - firstCell->boardIndexY) != ( secondCell->boardIndexX - firstCell->boardIndexX))
                return false;

            if( (secondCell->boardIndexY - firstCell->boardIndexY == 1)
            && (secondCell->boardIndexX - firstCell->boardIndexX == 1)
            )
                return true;

            else{
                int j = firstCell->boardIndexY + 1,i = firstCell->boardIndexX + 1;
                while(j < secondCell->boardIndexY && i < secondCell->boardIndexX){
                    temp = getBoardCell(i,j);
                    if(temp->associatedChessPieceIndex != -1) return false; //co quan nam giua 
                    i++;
                    j++;
                }
                return true;
            }
        }
        else if( (secondCell->boardIndexY < firstCell->boardIndexY)
        && (secondCell->boardIndexX > firstCell->boardIndexX)
        ) // di cheo ben phai xuong duoi
        {
            if((secondCell->boardIndexY - firstCell->boardIndexY) != -( secondCell->boardIndexX - firstCell->boardIndexX))
                return false;

            if( (secondCell->boardIndexY - firstCell->boardIndexY == -1)
                && (secondCell->boardIndexX - firstCell->boardIndexX == 1)
            ) 
                return true;

            else{
                int i = firstCell->boardIndexX + 1, j = firstCell->boardIndexY - 1;
                while(i < secondCell->boardIndexX && j > secondCell->boardIndexY){
                    temp = getBoardCell(i,j);
                    if(temp->associatedChessPieceIndex != -1) return false;
                    j--;
                    i++;
                }
                return true;
            }
        }

        else if( (secondCell->boardIndexY < firstCell->boardIndexY)
        && (secondCell->boardIndexX < firstCell->boardIndexX)
        ) // di cheo ben trai xuong duoi
        {
            if ((secondCell->boardIndexY - firstCell->boardIndexY) != ( secondCell->boardIndexX - firstCell->boardIndexX))
                return false;

            if( (secondCell->boardIndexY - firstCell->boardIndexY == -1)
            && (secondCell->boardIndexX - firstCell->boardIndexX == -1)
            )
                return true;

            else{
                int j = firstCell->boardIndexY - 1,i = firstCell->boardIndexX - 1;
                while(j > secondCell->boardIndexY && i > secondCell->boardIndexX){
                    temp = getBoardCell(i,j);
                    if(temp->associatedChessPieceIndex != -1) return false; //co quan nam giua
                    i--;
                    j--;
                }
                return true;
            }
        }

        else if( (secondCell->boardIndexY > firstCell->boardIndexY)
        && (secondCell->boardIndexX < firstCell->boardIndexX)
        ) // di cheo ben trai len tren
        {
            if((secondCell->boardIndexY - firstCell->boardIndexY) != -( secondCell->boardIndexX - firstCell->boardIndexX))
                return false;

            if( (secondCell->boardIndexY - firstCell->boardIndexY == 1)
                && (secondCell->boardIndexX - firstCell->boardIndexX == -1)
            ) 
                return true;

            else{
                int i = firstCell->boardIndexX - 1, j = firstCell->boardIndexY + 1;
                while(i > secondCell->boardIndexX && j < secondCell->boardIndexY){
                    temp = getBoardCell(i,j);
                    if(temp->associatedChessPieceIndex != -1) return false;
                    j++;
                    i--;
                }
                return true;
            }
        }
    }

    return false;
}

bool LogicGame::checkBishopMoveRule(ExtraModel *firstCell, ExtraModel *secondCell){
    ExtraModel* temp;

    if( (secondCell->boardIndexY != firstCell->boardIndexY)
        && (secondCell->boardIndexX != firstCell->boardIndexX)
        )
    {
        
        cout << "kiem tra hau di cheo" << endl;
        if( (secondCell->boardIndexY > firstCell->boardIndexY)
        && (secondCell->boardIndexX > firstCell->boardIndexX)
        ) // di cheo ben phai len tren
        {
            if ((secondCell->boardIndexY - firstCell->boardIndexY) != ( secondCell->boardIndexX - firstCell->boardIndexX))
                return false;

            if( (secondCell->boardIndexY - firstCell->boardIndexY == 1)
            && (secondCell->boardIndexX - firstCell->boardIndexX == 1)
            )
                return true;

            else{
                int j = firstCell->boardIndexY + 1,i = firstCell->boardIndexX + 1;
                while(j < secondCell->boardIndexY && i < secondCell->boardIndexX){
                    temp = getBoardCell(i,j);
                    if(temp->associatedChessPieceIndex != -1) return false; //co quan nam giua 
                    i++;
                    j++;
                }
                return true;
            }
        }
        else if( (secondCell->boardIndexY < firstCell->boardIndexY)
        && (secondCell->boardIndexX > firstCell->boardIndexX)
        ) // di cheo ben phai xuong duoi
        {
            if((secondCell->boardIndexY - firstCell->boardIndexY) != -( secondCell->boardIndexX - firstCell->boardIndexX))
                return false;

            if( (secondCell->boardIndexY - firstCell->boardIndexY == -1)
                && (secondCell->boardIndexX - firstCell->boardIndexX == 1)
            ) 
                return true;

            else{
                int i = firstCell->boardIndexX + 1, j = firstCell->boardIndexY - 1;
                while(i < secondCell->boardIndexX && j > secondCell->boardIndexY){
                    temp = getBoardCell(i,j);
                    if(temp->associatedChessPieceIndex != -1) return false;
                    j--;
                    i++;
                }
                return true;
            }
        }

        else if( (secondCell->boardIndexY < firstCell->boardIndexY)
        && (secondCell->boardIndexX < firstCell->boardIndexX)
        ) // di cheo ben trai xuong duoi
        {
            if ((secondCell->boardIndexY - firstCell->boardIndexY) != ( secondCell->boardIndexX - firstCell->boardIndexX))
                return false;

            if( (secondCell->boardIndexY - firstCell->boardIndexY == -1)
            && (secondCell->boardIndexX - firstCell->boardIndexX == -1)
            )
                return true;

            else{
                int j = firstCell->boardIndexY - 1,i = firstCell->boardIndexX - 1;
                while(j > secondCell->boardIndexY && i > secondCell->boardIndexX){
                    temp = getBoardCell(i,j);
                    if(temp->associatedChessPieceIndex != -1) return false; //co quan nam giua
                    i--;
                    j--;
                }
                return true;
            }
        }

        else if( (secondCell->boardIndexY > firstCell->boardIndexY)
        && (secondCell->boardIndexX < firstCell->boardIndexX)
        ) // di cheo ben trai len tren
        {
            if((secondCell->boardIndexY - firstCell->boardIndexY) != -( secondCell->boardIndexX - firstCell->boardIndexX))
                return false;

            if( (secondCell->boardIndexY - firstCell->boardIndexY == 1)
                && (secondCell->boardIndexX - firstCell->boardIndexX == -1)
            ) 
                return true;

            else{
                int i = firstCell->boardIndexX - 1, j = firstCell->boardIndexY + 1;
                while(i > secondCell->boardIndexX && j < secondCell->boardIndexY){
                    temp = getBoardCell(i,j);
                    if(temp->associatedChessPieceIndex != -1) return false;
                    j++;
                    i--;
                }
                return true;
            }
        }
    }
    
    return false;
}

bool LogicGame::checkRookMoveRule(ExtraModel *firstCell, ExtraModel *secondCell){
    ExtraModel* temp = NULL;
    /*di thang*/
    if( (secondCell->boardIndexX == firstCell->boardIndexX)
        && (secondCell->boardIndexY != firstCell->boardIndexY)
        )
    {
        cout << "hau di thang" << endl;

        if(secondCell->boardIndexY > firstCell->boardIndexY){//di thang len tren
            if((secondCell->boardIndexY - firstCell->boardIndexY == 1))
                return true;
            
            for(int i = firstCell->boardIndexY + 1; i < secondCell->boardIndexY ; i++){
                temp = getBoardCell(firstCell->boardIndexX,i);
                if(temp->associatedChessPieceIndex != -1) {
                    return false; // co quan nam giua firstcell va secondcell
                }
            }
            return true;
        }

        if(secondCell->boardIndexY < firstCell->boardIndexY){//di thang xuong duoi

            if((secondCell->boardIndexY - firstCell->boardIndexY == -1))
                return true;

            for(int i = firstCell->boardIndexY - 1; i > secondCell->boardIndexY ; i--){
                temp = getBoardCell(firstCell->boardIndexX,i);
                if(temp->associatedChessPieceIndex != -1) 
                {
                    return false; // co quan nam giua firstcell va secondcell
                }
            }
            return true;
        }

    }

    /*di ngang*/
    else if( (secondCell->boardIndexY == firstCell->boardIndexY)
        && (secondCell->boardIndexX != firstCell->boardIndexX)
        )
    {
        cout << "hau di ngang" << endl;

        if(secondCell->boardIndexX < firstCell->boardIndexX){//di ngang sang trai
            if((secondCell->boardIndexX - firstCell->boardIndexX == -1))
                return true;

            for(int i = firstCell->boardIndexX - 1; i > secondCell->boardIndexX ; i--){
                temp = getBoardCell(i,firstCell->boardIndexY);
                if(temp->associatedChessPieceIndex != -1) return false; // co quan nam giua firstcell va secondcell
            }

            return true;
        }

        if(secondCell->boardIndexX > firstCell->boardIndexX){//di ngang sang phai
            if((secondCell->boardIndexX - firstCell->boardIndexX == 1))
                return true;

            for(int i = firstCell->boardIndexX + 1; i < secondCell->boardIndexX ; i++){
                temp = getBoardCell(i,firstCell->boardIndexY);
                if(temp->associatedChessPieceIndex != -1) return false; // co quan nam giua firstcell va secondcell
            }

            return true;
        }

    }
    return false;
}

bool LogicGame::checkKnightMoveRule(ExtraModel *firstcell, ExtraModel *secondcell){
    if((secondcell->boardIndexY - firstcell->boardIndexY == 1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 2)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == -1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 2)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == 1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == -2)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == -1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == -2)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == 2)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == -2)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == 2)
        && (secondcell->boardIndexX - firstcell->boardIndexX == -1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == -2)
        && (secondcell->boardIndexX - firstcell->boardIndexX == -1)
        )
        return true;
    return false;
}

bool LogicGame::checkKingMoveRule(ExtraModel *firstcell, ExtraModel *secondcell){
    if((secondcell->boardIndexY - firstcell->boardIndexY == 1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == 0)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == -1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == -1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 0)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == -1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == -1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == 0)
        && (secondcell->boardIndexX - firstcell->boardIndexX == -1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == 1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == -1)
        )
        return true;
    if((secondcell->boardIndexY - firstcell->boardIndexY == 1)
        && (secondcell->boardIndexX - firstcell->boardIndexX == 0)
        )
        return true;
    return false;
}

ExtraModel* LogicGame::getBoardCell(int x, int y){
    ExtraModel* temp = NULL;
    bool found = false;

    for(int i = 0 ; i < BOARD_SIZE ; i++){
        for(int j = 0 ; j < BOARD_SIZE ; j++){
            if(GameScene::inst().allCells[j][i]->boardIndexX == x
                && GameScene::inst().allCells[j][i]->boardIndexY == y){
                found = true;
                //cout << "found" << endl;
                temp = GameScene::inst().allCells[j][i];
                break;
            }
        }
        if(found) break;
    }

    return temp;
}


void LogicGame::transformPawnToQueen(ExtraModel *prevSelectedCell,ExtraModel* currentSelectedCell , int prevSelectedChestPieceIndex){
    cout << "kiem tra luat bien thanh hau" << endl;

    if(currentSelectedCell->boardIndexY == 7 &&
                (prevSelectedCell->associatedChessPieceIndex >= 8 && prevSelectedCell->associatedChessPieceIndex <= 15)
                )//transform red pawn to red queen if it reach the highest row
    {
        GameScene::inst().models[prevSelectedChestPieceIndex] = NULL;
        GameScene::inst().models[prevSelectedChestPieceIndex] = new BaseModel();
        GameScene::inst().models[prevSelectedChestPieceIndex]->loadModel("Models/Queen.obj");
        GameScene::inst().models[prevSelectedChestPieceIndex]->transformedToQueen = true;

        Vector3 tempVec(currentSelectedCell->getPosition().x,9,currentSelectedCell->getPosition().z);
        GameScene::inst().models[prevSelectedChestPieceIndex]->setPosition(tempVec);
        cout << "transform to red queen" << endl;
    }
 
    else if(currentSelectedCell->boardIndexY == 0 &&
        (prevSelectedCell->associatedChessPieceIndex >= 16 && prevSelectedCell->associatedChessPieceIndex <= 23)
        )//transform blue pawn to blue queen if it reach the lowest row
    {
        GameScene::inst().models[prevSelectedChestPieceIndex] = NULL;
        GameScene::inst().models[prevSelectedChestPieceIndex] = new BaseModel();
        GameScene::inst().models[prevSelectedChestPieceIndex]->loadModel("Models/QueenBlue.obj");
        GameScene::inst().models[prevSelectedChestPieceIndex]->transformedToQueen = true;

        Vector3 tempVec(currentSelectedCell->getPosition().x,9,currentSelectedCell->getPosition().z);
        GameScene::inst().models[prevSelectedChestPieceIndex]->setPosition(tempVec);
        cout << "transform to blue queen" << endl;
    }
}

