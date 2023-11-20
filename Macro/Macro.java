import java.util.*;
import java.io.*;

class MDT {
    String macro_defn;

    MDT(String md) {
        this.macro_defn = md;
    }
};

class MNT {
    String name;
    int mdt_index;

    MNT(String n, int idx) {
        this.name = n;
        this.mdt_index = idx;
    }

    void Display() {
        System.out.println(this.name + "  " + this.mdt_index);
    }
};

class ALA {
    String arg;

    ALA(String a) {
        this.arg = a;
    }
};

public class Macro {
    static Vector<MNT> mnt = new Vector<MNT>();
    static Vector<MDT> mdt = new Vector<MDT>();
    static Vector<ALA> ala = new Vector<ALA>();

    public static Vector<Integer> find_in_mnt(String s) {
        Vector<Integer> op = new Vector<>();
        for (Integer i = 0; i < mnt.size(); i++) {
            if (mnt.elementAt(i).name.equals(s)) {
                op.add(mnt.elementAt(i).mdt_index + 1);
                if (i == mnt.size() - 1)
                    op.add(mdt.size() - 1);
                else
                    op.add(mnt.elementAt(i + 1).mdt_index - 1);
                return op;
            }
        }
        op.add(-1);
        op.add(-1);
        return op;
    }

    public static void writeMDT(Vector<MDT> m) throws Exception {
        PrintWriter mdtf = new PrintWriter("Macro/mdt.txt");
        for (MDT i : m) {
            mdtf.println(i.macro_defn);
        }
        mdtf.close();
    }

    public static void writeMNT(Vector<MNT> m) throws Exception {
        PrintWriter mdtf = new PrintWriter("Macro/mnt.txt");
        for (MNT i : m) {
            mdtf.println(i.name + " " + i.mdt_index);
        }
        mdtf.close();
    }

    public static void writeALA(Vector<ALA> m) throws Exception {
        PrintWriter mdtf = new PrintWriter("Macro/ala.txt");
        for (ALA i : m) {
            mdtf.println(i.arg);
        }
        mdtf.close();
    }

    public static int findArg(String ar, Vector<ALA> a) {
        for (int i = 0; i < a.size(); i++) {
            if (a.elementAt(i).arg.contains(ar))
                return i;
        }
        return -1;
    }

    public static void pass1() throws Exception {
        File input = new File("Macro/input.txt");
        Scanner sc = new Scanner(input);
        PrintWriter inter = new PrintWriter("Macro/intermidiate_code.txt");
        while (sc.hasNextLine()) {
            String s = sc.nextLine();
            if (s.equals("MACRO")) {

                String macro_data = sc.nextLine();
                String[] words = macro_data.split(" ");
                String[] param = words[1].split(",");

                for (String i : param) {
                    System.out.println(i);
                    ala.add(new ALA(i));
                }

                MNT m1 = new MNT(words[0], mdt.size());
                mnt.add(m1);

                MDT md = new MDT(macro_data);
                mdt.add(md);

                m1.Display();

                while (!s.equals("MEND")) {
                    s = sc.nextLine();
                    String[] sp = s.split(" ");
                    if (sp.length > 1) {
                        System.out.println(sp[1]);
                        String[] ar = sp[1].split(",");
                        s = sp[0]+" ";
                        for (String a : ar) {
                            System.out.println(a + " " + findArg(a, ala));
                            if(findArg(a, ala)!=-1) s += "&"+findArg(a, ala)+" ";
                            else s+=a+" ";
                        }
                    }
                    MDT m = new MDT(s);
                    mdt.add(m);
                }
            } else
                inter.println(s);
        }
        inter.close();
        sc.close();
        writeMDT(mdt);
        writeALA(ala);
        writeMNT(mnt);
    }

    public static void pass2() throws Exception {
        System.out.println("Pass2");
        File input = new File("Macro/intermidiate_code.txt");
        System.out.println("input file opened");
        PrintWriter output = new PrintWriter("Macro/output.txt");
        System.out.println("output file");
        Scanner sc = new Scanner(input);
        System.out.println("scanner");

        while (sc.hasNextLine()) {
            String s = sc.nextLine();
            String tokens[]=s.split(" ");
            if(tokens.length>=2){
                int macro_ind=find_in_mnt(tokens[0]).elementAt(0);
                int macro_ind_end=find_in_mnt(tokens[0]).elementAt(1);
                if(macro_ind==-1){
                    macro_ind=find_in_mnt(tokens[1]).elementAt(0);
                    macro_ind_end=find_in_mnt(tokens[1]).elementAt(1);
                }
                if(macro_ind!=-1){
                    System.out.println("Macro call to "+mdt.elementAt(macro_ind).macro_defn);
                    for(int i=macro_ind;i<=macro_ind_end;i++){
                        output.println(mdt.elementAt(i).macro_defn);
                        System.out.println(mdt.elementAt(i).macro_defn);
                    }
                }else{
                    output.println(s);
                }
            }
            else{
                output.println(s);
            }
        }
        output.close();
        sc.close();
    }

    public static void main(String args[]) {
        try {
            pass1();
            pass2();
        } catch (Exception e) {
            System.out.println("File not found " + e);
        }
    }
}