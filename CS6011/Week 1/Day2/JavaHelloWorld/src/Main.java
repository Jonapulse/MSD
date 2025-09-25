import java.util.Random;

public static void main() {
  System.out.println("Hello World");

  ArrayList<Integer> list = new ArrayList<>(10);
  Random rand = new Random();
  int sum = 0;
  for(int i = 0; i < 10; i++) {
      int randInt = rand.nextInt();
      list.add(randInt);
      sum += randInt;
      System.out.println(sum);
  }
  System.out.println("Sum: " + sum);

  Scanner s = new Scanner(System.in);
  System.out.println("Please input your name: ");
  String name = s.nextLine();
  System.out.println("Please input your age: ");
  int age = s.nextInt();
  String generation = "";
  boolean canVote = false;

  if(age > 18) {
    canVote = true;
  }
  if(age < 22)
      generation = "iGen";
  else if (age < 44)
      generation = "Millenial";
  else if (age < 60)
      generation = "Baby Boomer";
  else
      generation = "Greatest Generation";

  System.out.println("Hi, " + name + ". You " + (canVote ? "can": "cannot") +
          " vote, and are a member of the " + generation + " generation");

}
