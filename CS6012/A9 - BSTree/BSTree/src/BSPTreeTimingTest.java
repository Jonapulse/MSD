
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class BSPTreeTimingTest extends TimerTemplate {


    ArrayList<String> words;
    public BSPTreeTimingTest(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        words = getWordsFromFile("linuxwords.txt");
    }

    @Override
    protected void timingIteration(int n) {
        int collisions = 0;
        for(String word : words){
            if(hashTable.add(word))
                collisions++;
        }
        System.out.println("Collisions in test: " +  collisions);
    }

    @Override
    protected void compensationIteration(int n) {
        ChainingHashTable hashTable = new ChainingHashTable(100_000, new GoodHashFunctor());
        int collisions = 0;
        for(String word : words){
            collisions++;
        }
        System.out.println("Printing collisions for compensation: " +  collisions);
    }

    static ArrayList<String> getWordsFromFile(String filename) {
        ArrayList<String> words = new ArrayList<>();
        char[][] maze = null;
        try (Scanner fileIn = new Scanner(new File(filename))) {
            while(fileIn.hasNextLine()){
                words.add(fileIn.nextLine());
            }
        } catch(FileNotFoundException e){
            System.out.println("File not found");
        }
        return words;
    }

//    public static void main(String[] args) {
//        ArrayList<String> words = getWordsFromFile("linuxwords.txt");
//        System.out.println(words.size());
//    }
}
