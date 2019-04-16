public class Node {



    private int npx; //address of previous XOR address of next
    //address of next = address of previous XOR npx
    //address of previous == address of next XOR npx

    String name;
    public Node(int npx, String name){
        this.npx = npx;
        this.name = name;
    }

    public String getName(){
        return name;
    }

    public int getNpx() {
        return npx;
    }

    public void setNpx(int npx) {
        this.npx = npx;
    }

}

