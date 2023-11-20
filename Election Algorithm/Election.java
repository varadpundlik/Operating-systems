import java.util.*;

class Process{
		int id;
		boolean act;
		int link;
		Process(int id)
		{
			this.id = id;
			act = true;
			link=-1;
		}
	
}
class Election{

    int TotalProcess;
	Process[] process;
	public void initialise()
	{
		System.out.println("No of processes 5");
		TotalProcess = 5;
		process = new Process[TotalProcess];
		int i = 0;
		while (i < process.length) {
			process[i] = new Process(i);
			i++;
		}
	}

	public void createRing(){
		for(int i=0;i<TotalProcess;i++){
			process[i].link=(i+1)%TotalProcess;
		}
	}

    public void Ring(){
		createRing();
		int coord=FetchMaximum();
		System.out.println("Co-ordinator "+coord+" Fails");
		System.out.println("Election Initiated by 2");
		int initializedProcess = 2;
		Vector<Integer> active=new Vector<Integer>();
		int itr=initializedProcess;
		while(true){

			if(itr!=coord){ 
				active.add(itr);
				System.out.println("Process "+itr+" added in active list");
			}
			itr=process[itr].link;
			if(itr==initializedProcess) break;
		}
			
		int newCoord=Collections.max(active);
		System.out.println("Process "+newCoord+" becomes coordinator");

		itr=(initializedProcess+1)%TotalProcess;

		while(true){
			System.out.println("Process "+initializedProcess+" passed coordinator("+newCoord+") message to process "+itr);
			itr=(itr+1)%TotalProcess;
			if(itr==initializedProcess) break;

		}		
    }

    public int FetchMaximum()
	{
		int Ind = 0;
		int maxId = -9999;
		int i = 0;
		while (i < process.length) {
			if (process[i].act && process[i].id > maxId) {
				maxId = process[i].id;
				Ind = i;
			}
			i++;
		}
		return Ind;
	}

    public void Bully(){
		int coord=FetchMaximum();
        System.out.println("Coordinator "+coord+" fails");            
        process[coord].act = false;  
           
        int idOfInitiator = 1;  
        boolean overStatus = true;  
            
        while(overStatus){     
            boolean higherprocess = false;   
            for(int i = idOfInitiator + 1; i< TotalProcess; i++){  
                if(process[i].act==true){  
                    System.out.println("Process "+idOfInitiator+" Passes Election("+idOfInitiator+") message to process" +i);  
                    higherprocess = true;  
  
                }  
            }  
                
            if(higherprocess){   
                for(int i = idOfInitiator + 1; i< TotalProcess; i++){  
                    if(process[i].act==true){  
                        System.out.println("Process "+i+"Passes Ok("+i+") message to process" +idOfInitiator);  
                    }  
  
                }  
 
                idOfInitiator++;  
            }  
  
            else{   
                coord = process[FetchMaximum()].id;   
                System.out.println("Finally Process "+coord+" Becomes Coordinator");  
                 
                for(int i = coord - 1; i>= 0; i--){  
                    if(process[i].act==true){  
                        System.out.println("Process "+coord+"Passes Coordinator("+coord+") message to process " +i);  
                    }  
                }  
                  
                System.out.println("End of Election");  
                overStatus = false;  
                break;  
            }
		}  
    }

    public static void main(String args[]){
        Election object = new Election();
		object.initialise();
		System.out.println("Bully Election: \n\n");
		object.Bully();

		Election ob = new Election();
		ob.initialise();
		System.out.println("\n\nRing Election: \n\n");
		ob.Ring();
		
    }
}
