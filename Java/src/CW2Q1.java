import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class CW2Q1 {

    /**
     * uses iterative bubbles sort to order the list of strings
     * @param strings the array of strings to be sorted
     * @return a sorted array of strings
     */
    static String[] bubbleSort(String[] strings) {
        int n = strings.length;
        String temp;
        //iterates through all items in the array
        for(int i=0; i < n; i++){
            //checks each item against all non-sorted items
            for(int j=1; j < (n-i); j++){
                //ensures the sort ends when the array of strings is finished
                if(strings[j] == null){

                }
                //calls compare recursively to decide which string is earlier alphabetically
                //then makes any necessary swaps
                else if(compare(strings[j-1], strings[j], 0)){
                    temp = strings[j-1];
                    strings[j-1] = strings[j];
                    strings[j] = temp;
                }

            }


        }
        return strings;

    }

    /**
     * recursive function that compares two strings alphabetically
     * @param base the item that is stationary in the list
     * @param toCompare the item that is 'bubbling'(being compared to each other element) up the list
     * @param startValue the location of the character to start comparison on
     * @return true if a swap should be made
     */
    static boolean compare(String base, String toCompare, int startValue){
        //if one string is shorter than the other, it is valued as lower in the alphabet
            if (startValue > base.length() - 1) {
                return false;
            } else if (startValue > toCompare.length() - 1) {
                return true;
            }
            //if the characters are different they can be compared as expected
            if (base.charAt(startValue) > toCompare.charAt(startValue)) {
                return true;
                //if the are the same, the function is called again
                //with the index of the next character as the starting value
            } else if (base.charAt(startValue) == toCompare.charAt(startValue)) {
                return compare(base, toCompare, startValue + 1);
            } else {
                return false;
            }


    }

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
        }catch (FileNotFoundException e){
            System.out.println("file not found");
            return null;
        }
        catch (IOException e){
            System.out.println("IO error");
            return null;
        }
        String[] output = new String[counter];

        for(int i = 0; i < counter-1;i++){
            output[i] = inputStrings[i];
        }
        return output;


    }


    public static void main(String[] args){
        String[] sorted = bubbleSort(getStrings(args[0]));
        int i = 0;
        while( sorted[i] != null) {
            System.out.println(sorted[i]);
            i++;
        }
    }
}
