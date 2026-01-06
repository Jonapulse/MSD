import java.util.ArrayList;
import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class TicTacToe {

    private static ArrayList<Character> playGrid;
    private static boolean isOsTurn;
    private static char theWinner; //'O', 'X', and 'T' for tie
    private static int turnCounter;
    private final static int TURN_LIMIT = 9;

    //Could do an int board[3][3]
    //char board[3][3]; //blank '' for empty, 'letter

    TicTacToe() {

        isOsTurn = true;
        playGrid = new ArrayList<>();
        turnCounter = 0;
        for(int i = 0; i < 9; i++){
            playGrid.add(' ');
        }

    }

    private void showBoard(){
        //An example of what was bad
//        System.out.println( board[0] + board[1] + board[2]);
//        System.out.println( board[3] + board[4] + board[5]);
//        System.out.println( board[6] + board[7] + board[8]);
        String printStr = "";
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                printStr += "[" + playGrid.get(i + j * 3) + "]";
            }
            printStr += "\n";
        }
        System.out.println(printStr);
    }

    private void doPlayerTurn() {
        String playerName = isOsTurn ? "Player 1" :  "Player 2";
        System.out.println(playerName + ", choose a square to place in");

        Scanner input = new Scanner(System.in);
        int square = input.nextInt();
        while(playGrid.get(square) != ' '){
            System.out.println("Invalid square, try again");
            square = input.nextInt();
        }

        playGrid.set(square, isOsTurn ? 'O' : 'X');
        turnCounter++;
        isOsTurn = !isOsTurn;

    }

    private boolean gameComplete(){
        //Check Horizontal values
        for(int i = 0; i < 9; i += 3){
            //And they aren't blank
            if((playGrid.get(i) != ' ') && (playGrid.get(i) == playGrid.get(i + 1)) && (playGrid.get(i + 1)) == playGrid.get(i + 2)) {
                theWinner = playGrid.get(i) == 'O' ? '0' : 'X';
                return true;
            }
        }

        //Check Vertical
        for(int i = 0; i < 3; i ++){
            //And they aren't blank
            if((playGrid.get(i) != ' ') && (playGrid.get(i) == playGrid.get(i + 3)) && (playGrid.get(i + 3)) == playGrid.get(i + 6)) {
                theWinner = playGrid.get(i) == 'O' ?  '0' : 'X';
                return true;
            }
        }

        //Check Top Left to Bottom Right
        if((playGrid.get(0) != ' ') && (playGrid.get(0) == playGrid.get(4)) && (playGrid.get(4)) == playGrid.get(8)) {
            theWinner = playGrid.get(0) == 'O' ? '0' : 'X';
            return true;
        }

        //Check Top Right to Bottom Left
        //Check Top Left to Bottom Right
        if((playGrid.get(2) != ' ') && (playGrid.get(2) == playGrid.get(4)) && (playGrid.get(4)) == playGrid.get(6)) {
            theWinner = playGrid.get(2) == 'O' ? '0' : 'X';
            return true;
        }

        if(turnCounter == TURN_LIMIT){
            theWinner = 'T';
            return true;
        }
        return false;
    }

    void printWinner(){
        if(theWinner == 'O'){
            System.out.println("O has won!");
        }
        else if (theWinner == 'X'){
            System.out.println("X has won!");
        }
        else
            System.out.println("Draw!");
    }

    void main() {
        //Tic Tac
        TicTacToe game = new TicTacToe();
        game.showBoard();

        while(!game.gameComplete()) {
            game.doPlayerTurn();
            game.showBoard();
        }

        game.printWinner();
    }
}

