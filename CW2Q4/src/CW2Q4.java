import java.io.*;
import java.util.Scanner;


public class CW2Q4 {
    static Node[] mockMemory = new Node[8192];
    static int currentHeadLocation = 0;
    static int currentEndLocation = 0;

    static String[] getStrings(String filePath){
        //ArrayList<String> inputStrings = new ArrayList<>();
        String[] inputStrings = new String[8192];
        int counter = 0;

        try {
            FileReader fileReader = new FileReader(filePath);

            int nextInt = fileReader.read();
            //System.out.println(nextInt);
            String currentString ="";
            char nextChar;
            while (nextInt != -1){
                nextChar = (char)nextInt;
                //System.out.println(nextChar);

                if(nextChar == '"'){

                }else if(nextChar == ','){
                    inputStrings[counter] = currentString;

                    currentString ="";
                    counter++;
                }
                else {
                    currentString = currentString + nextChar;


                }
                nextInt = fileReader.read();

            }
            inputStrings[counter] = currentString;
            counter++;
        }catch (FileNotFoundException e){
            System.out.println("file not found");
            return null;
        }
        catch (IOException e){
            System.out.println("IO error");
            return null;
        }
        String[] output = new String[counter];

        for(int i = 0; i <= counter-1;i++){
            output[i] = inputStrings[i];
        }
        return output;
    }

    private static int[] findNode(String name, int start){
        int currentAddress = currentHeadLocation;
        int nextAddress = mockMemory[currentHeadLocation].getNpx();

        while(!mockMemory[currentAddress].getName().equals(name)) {
           int  holder = nextAddress;
            nextAddress = currentAddress ^ mockMemory[nextAddress].getNpx();

            currentAddress = holder;
        }
        int[] output = {currentAddress, nextAddress};
        return output;
    }

    public static void insertAfter(String after, String newObj){
        int[] replaceAndNext = findNode(after, 0);

        int replaceAdr = replaceAndNext[0];
        int nextAdr = replaceAndNext[1];
        int newAdr = findUnoccupied();
        int replaceNpx = mockMemory[replaceAdr].getNpx();

        mockMemory[newAdr] = new Node(replaceAdr ^ nextAdr, newObj);
        mockMemory[replaceAdr].setNpx((replaceNpx ^ nextAdr) ^ newAdr);
        mockMemory[nextAdr].setNpx((mockMemory[nextAdr].getNpx() ^ replaceAdr) ^ newAdr);
    }

    public static void insertBefore(String before, String newObj){
        int[] replaceAndNext = findNode(before, 0);
        int replaceAdr = replaceAndNext[0];
        int replaceNpx = mockMemory[replaceAdr].getNpx();
        int previousAdr = replaceAndNext[1]^ replaceNpx;
        int newAdr = findUnoccupied();

        mockMemory[newAdr] = new Node(replaceAdr^previousAdr, newObj);
        mockMemory[replaceAdr].setNpx((replaceNpx^previousAdr)^newAdr);
        mockMemory[previousAdr].setNpx((mockMemory[previousAdr].getNpx()^replaceAdr)^newAdr);
    }

    public static String removeAfter(String after){
        int[] inputAndToRemove = findNode(after, 0);
        int toRemoveAdr = inputAndToRemove[1];
        int inputAdr = inputAndToRemove[0];
        int toRemoveNpx = mockMemory[toRemoveAdr].getNpx();
        int nextAdr = toRemoveNpx ^ inputAdr;
        String removed = mockMemory[toRemoveAdr].getName();

        mockMemory[nextAdr].setNpx((toRemoveAdr^mockMemory[nextAdr].getNpx())^inputAdr);
        mockMemory[inputAdr].setNpx((toRemoveAdr^mockMemory[inputAdr].getNpx())^nextAdr);
        mockMemory[toRemoveAdr] = null;

        return removed;
    }

    public static String removeBefore(String before){
        int[] inputAndAfter = findNode(before, 0);
        int inputAdr = inputAndAfter[0];
        int inputNpx = mockMemory[inputAdr].getNpx();
        int toRemoveAdr = inputNpx ^ inputAndAfter[1];
        int toRemoveNpx = mockMemory[toRemoveAdr].getNpx();
        int previousAdr = toRemoveNpx ^ inputAdr;

        String removed = mockMemory[toRemoveAdr].getName();

        mockMemory[previousAdr].setNpx((toRemoveAdr^mockMemory[previousAdr].getNpx())^inputAdr);
        mockMemory[inputAdr].setNpx((toRemoveAdr^mockMemory[inputAdr].getNpx())^previousAdr);
        mockMemory[toRemoveAdr] = null;

        return removed;
    }

    public static void insertAtFront(String newObj){
        String toAdd = newObj;
        int addressToAdd = findUnoccupied();

        mockMemory[addressToAdd] = new Node(currentEndLocation^0,toAdd);
        mockMemory[currentEndLocation].setNpx(addressToAdd^mockMemory[currentEndLocation].getNpx());
        currentEndLocation = addressToAdd;
    }

    private static int findUnoccupied(){
        int currentIndex = 0;
        while (mockMemory[currentIndex] != null){
            currentIndex++;
            if(currentIndex == 8191){
                System.out.println("Mock Memory full");
            }
        }

        return currentIndex;
    }

    private static void printToCommandLine(){
        int currentAdr = currentHeadLocation;
        int previousAdr = 0;
        int currentNpx;
        while (currentAdr != currentEndLocation){
            System.out.println(mockMemory[currentAdr].getName());
            System.out.println(currentAdr);
            System.out.println(previousAdr);
            currentNpx = mockMemory[currentAdr].getNpx();
            currentAdr = getNext(previousAdr, currentNpx);
            previousAdr = currentAdr;
        }
        System.out.println(mockMemory[currentAdr].getName());

    }

    static void printToFile( String filePath){
        try {
            PrintWriter writer = new PrintWriter(new FileWriter(filePath));
            for (Node node:mockMemory
            ) {
                if(node != null) {
                    writer.printf("%c%s%c,", '"', node.getName(), '"');
                }else {
                }
                writer.close();
            }
        }catch (FileNotFoundException e){
            System.out.println("file not found");
        }catch (IOException e){
            System.out.println("IO error");
        }
    }

    static int getNext(int previousAdr, int npx){
        return previousAdr^npx;
    }

    public static void main(String[] args){


        String[] names = getStrings(args[0]);
        currentHeadLocation = findUnoccupied();
        for (int i = 0; i<=names.length-1; i++) {
            insertAtFront(names[i]);
        }


        Scanner scanner = new Scanner(System.in);


        while(true){
            System.out.println("\nWhich action would you like to take?");
            System.out.println("Type 1 to print to command line");
            System.out.println("Type 2 to print to file");
            System.out.println("Type 3 to insert an item");
            System.out.println("Type 4 to delete an item");

            switch (scanner.next()){
                case ("1"):
                    printToCommandLine();
                    break;
                case ("2"):
                    printToFile(args[0]);
                    break;
                case ("3"):
                    System.out.println("Type the word you wish to insert");
                    String toInsert = scanner.next();
                    System.out.println("Type the word you wish to use to define the location");
                    String toLocate = scanner.next();
                    System.out.println("Type B to insert before");
                    System.out.println("Type A to insert after");
                    switch (scanner.next()){
                        case ("B"):
                            insertBefore(toLocate,toInsert);
                        case ("A"):
                            insertAfter(toLocate, toInsert);
                            default:
                    }

                    break;
                case ("4"):
                    System.out.println("Type B to delete before");
                    System.out.println("Type A to delete after");
                    switch (scanner.next()){
                        case ("B"):
                            System.out.println("What word do you wish to delete before?");
                            System.out.println("You deleted " + removeBefore(scanner.next()) );
                            break;
                        case ("A"):
                            System.out.println("What word do you wish to delete after?");
                            System.out.println("You deleted " + removeAfter(scanner.next()) );
                            break;
                            default:
                    }
                    break;
                    default:


            }
        }


    }
}
