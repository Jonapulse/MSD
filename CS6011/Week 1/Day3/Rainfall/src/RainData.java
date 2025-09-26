//Created by Jon Pulsipher
//CS 6011
//u0294347
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class RainData{
    private ArrayList<String> month = new ArrayList<>();
    private ArrayList<Integer> year = new ArrayList<>();
    private ArrayList<Float> rain = new ArrayList<>();

    void ReadFileData(String fileName) throws FileNotFoundException {
        Scanner fileReader = new Scanner(new FileInputStream(fileName));
        String state = fileReader.nextLine();
        while(fileReader.hasNext())
        {
            month.add(fileReader.next());
            year.add(fileReader.nextInt());
            rain.add(fileReader.nextFloat());
        }
        fileReader.close();
    }

    RainData(String fileName){
        try{
            ReadFileData(fileName);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        };
    }

    public ArrayList<String> calculateMonthlyAverageRainfall(){
        //String mpnthlyRainfall = String.format("%.2f", sumRainfall);
        return null;
    }

    void main(String[] args) {
        try{
            PrintWriter pw = new PrintWriter("src/rainfall_data.txt");

            //Should we employ some data cleaning? Like if it was misspelled or something was missed
        } catch (FileNotFoundException e)
        {
            throw new RuntimeException(e);
        }
    }
}

