public class CW2Q8 {

    /**
     * recursively calls the formula to get the sum of the next ring in
     * @param ringNumber the number of the ring that is currently being calculated
     * @return the sum of the diagonals for that ring and all within it
     */
     private static int getSum(int ringNumber){
         //base case
         if(ringNumber == 0){
             return 1;
         }
         return 4*(2*ringNumber+1)*(2*ringNumber+1) -12*ringNumber + getSum(ringNumber-1);
     }


    public static void main(String args[]){
            System.out.println(getSum((Integer.parseInt(args[0])-1)/2));
    }
}
