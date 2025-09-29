//Created by Jon Pulsipher
//CS 6011
//u0294347
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.sql.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class RainData{
    private HashMap<String, ArrayList<Double>> monthlyRainfall;
    private static String cityName;

    void ReadFileData(String fileName) throws FileNotFoundException {
        Scanner fileReader = new Scanner(new FileInputStream(fileName));
        cityName = fileReader.nextLine();
        monthlyRainfall = new HashMap<>();
        while(fileReader.hasNext())
        {
            String month = fileReader.next();
            fileReader.nextInt(); //Discard monthData
            double rainFallInches = fileReader.nextFloat();
            if(monthlyRainfall.containsKey(month))
                monthlyRainfall.get(month).add(rainFallInches);
            else {
                ArrayList oneMonthRainfall = new ArrayList();
                oneMonthRainfall.add(rainFallInches);
                monthlyRainfall.put(month, oneMonthRainfall);
            }
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

    public String GetPrintRainData()
    {
        String printStr = "";
        for(Map.Entry<String, ArrayList<Double>> entry : monthlyRainfall.entrySet())
        {
            String monthName = entry.getKey();
            ArrayList<Double> rainfallInchesForMonth = entry.getValue();
            double sum = 0;
            for(Double rainfallInches : rainfallInchesForMonth)
                sum += rainfallInches;
            double averageRainfall = sum  /rainfallInchesForMonth.size();

            String formattedRainfall = String.format("%.2f", averageRainfall);
            printStr += monthName + " " + formattedRainfall + "\n";
        }
        return printStr;
    }


    public static void main() {
        RainData rd = new RainData("src/Macon.txt");

        try{
            PrintWriter pw = new PrintWriter("src/rainfall_results.txt");
            pw.write(rd.GetPrintRainData());
            pw.close();
        } catch (FileNotFoundException e)
        {
            throw new RuntimeException(e);
        }
    }
}

