#include <iostream> 
#include <iostream>
#include <climits>
using namespace std;
const char x = 'X'; const char o = 'O'; const char null = '.';
std::string playboard = "...\n...\n...\n";
int Game_State()
{
    char player[2] = {x,o};
    bool HasEmptySpot = 0;

    for (int i = 0;i < 2;i++)
    {//Check for each player
        int count[4] = {0,0,0,0}; //Check for each direction
        for (int r = 0;r < 3;r++)
        {
            for (int c = 0;c < 3;c++)
            {
                if (playboard[r * 4 + c] == player[i]) { count[0]++; } //count horizontally
                if (playboard[c * 4 + r] == player[i]) { count[1]++; } //count vertically
                if (r == c && playboard[r * 4 + c]== player[i]) { count[2]++; } //count along - diagonal
                if (r + c == 2 && playboard[r * 4 + c] == player[i]) { count[3]++; }  //count along + diagonal
                if (playboard[r * 4 + c] == null)HasEmptySpot = 1;
            }
            for (int m = 0;m < 4;m++)
            {
                if (count[m] == 3) { return (i == 0) ? 1 : -1;}
            }
            count[0] = 0;count[1] = 0; //reset only for orthogonal directions
        }
    }
    return (HasEmptySpot) ? 2 : 0;
}
/**** Alpha-Beta Pruning Technique is implemented in this function ****/
int minimax(int depth, bool maximizingplayer, int alpha, int beta)
{
    int p = Game_State();
    if (abs(p) == 1 || p == 0 )return 100*p; //Return 100 if X won, -100 if O won, and 0 if draw.

    int MaxEval = -1000, MinEval = 1000; //scores for maximising and minimising players
    for (int i = 0;i < playboard.length();i++)
    {
         if (playboard[i] == null) {
               playboard[i]= maximizingplayer? x:o;
               if (maximizingplayer)
               {
                   MaxEval = std::max(MaxEval, minimax(depth+1,0,alpha,beta) - depth);
                   alpha = std::max(alpha, MaxEval);
               }
               else
               {
                   MinEval = std::min(MinEval, minimax(depth+1, 1,alpha,beta) + depth);
                   beta = std::min(beta, MinEval);
               }
                playboard[i] = null;
               if (beta <= alpha) break;
         }
    }
    return maximizingplayer==1 ? MaxEval : MinEval;
}
void Botmove()
{
    int bestmove=-1, MaxEval = INT_MIN;

    for (int i = 0;i < playboard.length();i++)
    {
        if (playboard[i] == null)
        {
            playboard[i] = x;
            int eval = minimax(0, 0,-9999,9999);
            if (eval > MaxEval)
            {
                bestmove = i;
                MaxEval = eval;
            }
            playboard[i] = null;
        }
    }
    playboard[bestmove] = x;
}
int main()
{
    bool Botturn=0; int state = 2,r,c;
    cout<<"PlayBot is ready to play !!"<<'\n';
    cout<<'\n';
    cout<<"Enter the row and column number (space-separated) at your move"<<'\n';
    cout<<'\n';
    cout<<"You are playing as O!"<<'\n';
    std::cout << "Enter 1 if PlayBot should start else enter 0 and play your first move";
    cout<<'\n';
    std::cin >> Botturn;
    while (state == 2)
    {
         if (Botturn)
         {
             Botmove();
             
         }
         else
         {
            std::cin >> r>>c;
            if(playboard[4*(r-1)+c-1] == null)
            {
                playboard[4 * (r - 1) + c - 1] = o;
            }
        }
        state = Game_State();
        Botturn = !(Botturn); 
        std::cout << playboard <<"\n";
    }
    std::cout << ((state == 1) ? "PlayBot won!" : "Draw") << "\n";
}
