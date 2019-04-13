import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;


public class CW2Q4 {
    static Node[] mockMemory = new Node[8192];
    static int currentHeadLocation = 0;


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

    public static void insertAtEnd(String newObj){
        String toAdd = newObj;
        int addressToAdd = findUnoccupied();

        mockMemory[addressToAdd] = new Node(currentHeadLocation^0,toAdd);
        //added node at next free
        mockMemory[currentHeadLocation].setNpx(addressToAdd^ mockMemory[currentHeadLocation].getNpx());
        currentHeadLocation = addressToAdd;
        //System.out.println(mockMemory[currentHeadLocation].getName() + " " + currentHeadLocation);
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



    public static void main(String args[]){
        for (String name:getStrings(args[0])
             ) {
            insertAtEnd(name);

        }


        insertAfter("PATRICIA", "AYYLMAO");
        System.out.println(removeBefore("AYYLMAO"));
        for (Node node:mockMemory
        ) {
            if(node != null) {
                System.out.println(node.getName());
            }else {
                System.out.print("X");
            }

        }

    }
}
