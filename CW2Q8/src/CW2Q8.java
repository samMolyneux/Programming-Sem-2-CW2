public class CW2Q8 {

     private static int getSum(int ringNumber){
         if(ringNumber == 0){
             return 1;
         }
         return 4*(2*ringNumber+1)*(2*ringNumber+1) -12*ringNumber + getSum(ringNumber-1);
     }


    public static void main(String args[]){
            System.out.println(getSum((Integer.parseInt(args[0])-1)/2));
    }
}
