public class CW2Q1 {

    String[] strings = {"az", "bzz", "aa", "ba", "bz", "bzz"};

    static String[] bubbleSort(String[] arr) {
        int n = arr.length;
        String temp;
        for(int i=0; i < n; i++){

            for(int j=1; j < (n-i); j++){
                if(compare(arr[j-1], arr[j], 0)){

                    //swap elements
                    temp = arr[j-1];
                    arr[j-1] = arr[j];
                    arr[j] = temp;
                }

            }

        }
        return arr;

    }
    static boolean compare(String base, String toCompare, int startValue){
        if (startValue > base.length()-1){
            return false;
        }else if (startValue > toCompare.length() -1){
            return true;
        }
        if(base.charAt(startValue) > toCompare.charAt(startValue)){
            return true;
        }else if(base.charAt(startValue) == toCompare.charAt(startValue)){
            return compare(base, toCompare, startValue +1 );
        }else{
            return false;
        }

    }


    public static void main(String[] args){
        System.out.println("test");
        String[] sorted = bubbleSort(args);
        for(int i =0; i<=sorted.length -1; i++ )
        System.out.println(sorted[i]);
    }
}
