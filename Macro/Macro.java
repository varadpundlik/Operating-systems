import java.util.*;
import java.io.*;

class MDT{
    String macro_defn;

    MDT(String md){
        this.macro_defn=md;
    }
};

class MNT{
    String name;
    int mdt_index;

    MNT(String n,int idx){
        this.name=n;
        this.mdt_index=idx;
    }
};

class ALA{
    String arg;

    ALA(String a){
        this.arg=a;
    }
};

public class Macro{
    Vector<MNT> mnt=new Vector<MNT>();
    Vector<MDT> mdt=new Vector<MDT>();
    Vector<ALA> ala=new Vector<ALA>();

    public static void pass1() throws Exception{
        File input=new File("input.txt");
        Scanner sc=new Scanner(input);

        while (sc.hasNextLine())
            System.out.println(sc.nextLine());
    }

    public static void pass2(){

    }

    public static void main(String args[]){
        System.out.println("Hello World");
        try{
            pass1();
        }catch(Exception e){
            System.out.println("File not found");
        }
    }
}
