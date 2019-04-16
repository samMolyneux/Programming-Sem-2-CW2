import java.io.*;
import java.util.Scanner;


public class CW2Q4 {
    static Node[] mockMemory = new Node[8192];
    static int currentHeadLocation = 0;

    /**
     * Gets the strings from the file
     * @param filePath the source file
     * @return an array of unformatted strings
     */
    static String[] getStrings(String filePath){
        //ArrayList<String> inputStrings = new ArrayList<>();
        String[] inputStrings = new String[8192];
        int counter = 0;

        try {
            FileReader fileReader = new FileReader(filePath);

            int nextInt = fileReader.read();
            String currentString ="";
            char nextChar;
            while (nextInt != -1){
                nextChar = (char)nextInt;

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

    /**
     * Finds a node and the next node to be used as a reference
     * @param name the name to search for
     * @param start the placec to start searching from
     * @return an array holding the address searched for then the next
     */
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
    /**
     * Inserts a new node after the given word, updates npx values
     * @param after the node to use as a reference
     * @param newObj the string to add to the list
     */
    public static void insertAfter(String after, String newObj){
        int[] replaceAndNext = findNode(after, 0);

        int replaceAdr = replaceAndNext[0];
        int nextAdr = replaceAndNext[1];
        int newAdr = findUnoccupied();
        int replaceNpx = mockMemory[replaceAdr].getNpx();

        mockMemory[newAdr] = new Node(replaceAdr ^ nextAdr, newObj);
        mockMemory[replaceAdr].setNpx((replaceNpx ^ nextAdr) ^ newAdr);
        if(mockMemory[nextAdr]!= null) {
            mockMemory[nextAdr].setNpx((mockMemory[nextAdr].getNpx() ^ replaceAdr) ^ newAdr);
        }

        if(mockMemory[nextAdr]!=null) {
            mockMemory[nextAdr].setNpx((mockMemory[nextAdr].getNpx() ^ replaceAdr) ^ newAdr);
        }
    }

    /**
     * Inserts a new node before the given word, updates npx values
     * @param before the node to use as a reference
     * @param newObj the string to add to the list
     */
    public static void insertBefore(String before, String newObj){
        int[] replaceAndNext = findNode(before, 0);
        int replaceAdr = replaceAndNext[0];
        int replaceNpx = mockMemory[replaceAdr].getNpx();
        int previousAdr = replaceAndNext[1]^ replaceNpx;
        int newAdr = findUnoccupied();

        mockMemory[newAdr] = new Node(replaceAdr^previousAdr, newObj);
        mockMemory[replaceAdr].setNpx((replaceNpx^previousAdr)^newAdr);
        if(mockMemory[previousAdr]!=null) {
            mockMemory[previousAdr].setNpx((mockMemory[previousAdr].getNpx() ^ replaceAdr) ^ newAdr);
        }
    }
    /**
     * removes the item after the given value in the list, updates the npx values
     * @param after the item to use as a reference point
     * @return the string that was removed
     */
    public static String removeAfter(String after){
        int[] inputAndToRemove = findNode(after, 0);
        int toRemoveAdr = inputAndToRemove[1];
        int inputAdr = inputAndToRemove[0];
        if(mockMemory[toRemoveAdr] != null){
            int toRemoveNpx = mockMemory[toRemoveAdr].getNpx();
            int nextAdr = toRemoveNpx ^ inputAdr;
            String removed = mockMemory[toRemoveAdr].getName();
            if(mockMemory[nextAdr]!= null) {

                mockMemory[nextAdr].setNpx((toRemoveAdr ^ mockMemory[nextAdr].getNpx()) ^ inputAdr);
            }
            mockMemory[inputAdr].setNpx((toRemoveAdr ^ mockMemory[inputAdr].getNpx()) ^ nextAdr);
            mockMemory[toRemoveAdr] = null;

            return removed;
        }
        return "NO SUCH ELEMENT";
    }

    /**
     * removes the item before the given value in the list, updates the npx values
     * @param before the item to use as a reference point
     * @return the string that was removed
     */
    public static String removeBefore(String before){
        int[] inputAndAfter = findNode(before, 0);
        int inputAdr = inputAndAfter[0];
        int inputNpx = mockMemory[inputAdr].getNpx();
        int toRemoveAdr = inputNpx ^ inputAndAfter[1];
        if(mockMemory[toRemoveAdr] != null) {
            int toRemoveNpx = mockMemory[toRemoveAdr].getNpx();
            int previousAdr = toRemoveNpx ^ inputAdr;
            String removed = mockMemory[toRemoveAdr].getName();
            if(mockMemory[previousAdr]!= null) {
                mockMemory[previousAdr].setNpx((toRemoveAdr ^ mockMemory[previousAdr].getNpx()) ^ inputAdr);
            }
            mockMemory[inputAdr].setNpx((toRemoveAdr ^ mockMemory[inputAdr].getNpx()) ^ previousAdr);
            mockMemory[toRemoveAdr] = null;

            return removed;
        }
        return "NO SUCH ELEMENT";
    }

    /**
     * Inserts a new item as the head of the list
     * @param newObj the word to be added
     */
    public static void insertAtFront(String newObj){
        String toAdd = newObj;
        int addressToAdd = findUnoccupied();

        mockMemory[addressToAdd] = new Node(currentHeadLocation^0, toAdd);

        if(currentHeadLocation!= 0){
            int addressNext = (mockMemory[currentHeadLocation].getNpx()^0);
            mockMemory[currentHeadLocation].setNpx(addressToAdd ^ addressNext);
        }
        currentHeadLocation = addressToAdd;
    }

    /**
     * Find the next unoccupied space in mock memory
     * @return the index of the free space
     */
    private static int findUnoccupied(){
        int currentIndex = 1;
        while (mockMemory[currentIndex] != null){
            currentIndex++;
            if(currentIndex == 8191){
                System.out.println("Mock Memory full");
            }
        }

        return currentIndex;
    }

    /**
     * Prints the list to the command line in order
     */
    private static void printToCommandLine(){
        int currentAdr = currentHeadLocation;
        int previousAdr = 0;
        int nextAdr;

        while (mockMemory[currentAdr]!=null){
            System.out.println(mockMemory[currentAdr].getName());

            nextAdr = previousAdr ^ mockMemory[currentAdr].getNpx();

            previousAdr = currentAdr;
            currentAdr = nextAdr;
        }

    }

    /**
     * Prints the list to the file in order
     * @param filePath the file to output to
     */
    static void printToFile( String filePath){
        try {
            PrintWriter writer = new PrintWriter(new FileWriter(filePath));

            int currentAdr = currentHeadLocation;
            int previousAdr = 0;
            int nextAdr;

            while (mockMemory[currentAdr]!=null){
                writer.printf("%c%s%c,", '"', mockMemory[currentAdr].getName(), '"');

                nextAdr = previousAdr ^ mockMemory[currentAdr].getNpx();

                previousAdr = currentAdr;
                currentAdr = nextAdr;
            }
            writer.close();
        }catch (FileNotFoundException e){
            System.out.println("file not found");
        }catch (IOException e){
            System.out.println("IO error");
        }
    }


    public static void main(String[] args){

        //adds all the names to the front of the list
        //done in the reverse order of the file so that first in file is first in list
        String[] names = getStrings(args[0]);
        currentHeadLocation = findUnoccupied();
        for (int i = names.length-1; i>=0; i--) {
            if(names[i]!= null) {
                insertAtFront(names[i]);
            }
        }


        Scanner scanner = new Scanner(System.in);

        //The interface
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
